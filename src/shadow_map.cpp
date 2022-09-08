#include "shadow_map.hpp"

#include <vector>
#include <algorithm>

#include <GL/glew.h>

void shadow_map::start() {
	m_terrain = get_parent()->get_component<terrain_component*>(1);
	m_fbo = get_render().add_fbo(200, 200);
	
	m_fbo->bind_frame(1);
	
	m_shadow_mesh = get_render().add_mesh();
	m_shadow_mesh->init(nullptr, 14 * 14 * 3 * 2 + 1);
}

void shadow_map::tick() {
	loli::vec2 pos = loli::vec2(get_cam().get_transform().get_pos().get_x(), get_cam().get_transform().get_pos().get_y());
	map(pos, 10.0);
}

void shadow_map::render() {
	float z = get_cam().get_proj().get(6);
	get_cam().get_proj().set(6, 0);
	
	get_render().bind_shader(1);
	m_fbo->bind();
	
	get_render().clear();
	get_render().viewport(0, 0, m_fbo->get_width(), m_fbo->get_height());
	
	get_render().get_shader()->uniform_mat4("u_transform", get_cam().to_projected_view(get_transform().get_mat()));
	
	get_render().bind_mesh(m_shadow_mesh);
	get_render().draw_arrays(loli::render_engine::triangle_fan, 0, m_shadow_size);
	
	get_render().viewport(0, 0, 800, 600);
	
	m_fbo->unbind();
	get_render().bind_shader(0);
	get_render().get_shader()->uniform_mat4("u_light_mat", get_cam().to_projected_view(get_transform().get_mat()));
	
	get_cam().get_proj().set(6, z);
}

loli::vec2 shadow_map::raycast(loli::vec2 pos, float dir, int range) {
	loli::vec2 raydir = loli::vec2(cos(dir), sin(dir));
	loli::vec2 delta = loli::vec2(abs(1.0 / raydir.get_x()), abs(1.0 / raydir.get_y()));
	loli::vec2 map = loli::vec2(floor(pos.get_x()), floor(pos.get_y()));
	
	loli::vec2 step, dist;
	
	if (raydir.get_x() < 0) {
		step.set_x(-1);
		dist.set_x((pos.get_x() - map.get_x()) * delta.get_x());
	} else {
		step.set_x(1);
		dist.set_x((map.get_x() + 1 - pos.get_x()) * delta.get_x());
	}
	
	if (raydir.get_y() < 0) {
		step.set_y(-1);
		dist.set_y((pos.get_y() - map.get_y()) * delta.get_y());
	} else {
		step.set_y(1);
		dist.set_y((map.get_y() + 1 - pos.get_y()) * delta.get_y());
	}
	
	bool side = false;
	bool hit = false;
	
	for (int i = 0; i < range + 1; i++) {
		if (dist.get_x() < dist.get_y()) {
			map.set_x(map.get_x() + step.get_x());
			dist.set_x(dist.get_x() + delta.get_x());
			side = true;
		} else {
			map.set_y(map.get_y() + step.get_y());
			dist.set_y(dist.get_y() + delta.get_y());
			side = false;
		}
		
		if (m_terrain->get(map.get_x(), map.get_y()) & terrain_component::OPAQUE) {
			hit = true;
			break;
		}
	}
	
	if (side) {
		float d = map.get_x() - pos.get_x() + (1 - step.get_x()) / 2;
		float m = sin(dir) / cos(dir);
		
		d += (d < 0 ? -1 : 1) * 0.05;
		
		return loli::vec2(pos.get_x() + d, pos.get_y() + d * m);
	} else {
		float d = map.get_y() - pos.get_y() + (1 - step.get_y()) / 2;
		float m = cos(dir) / sin(dir);
		
		d += (d < 0 ? -1 : 1) * 0.05;
		
		return loli::vec2(pos.get_x() + d * m, pos.get_y() + d);
	}
}

void shadow_map::map(loli::vec2 light_pos, int radius) {
	std::vector<ray> rays;
	std::vector<float> duplicates;
	
	int startx = -radius / 2 + (int) light_pos.get_x();
	int starty = -radius / 2 + (int) light_pos.get_y();
	
	int endx = radius / 2 + (int) light_pos.get_x();
	int endy = radius / 2 + (int) light_pos.get_y();
	
	startx = std::max(startx, 0);
	starty = std::max(starty, 0);

	endx = std::min(endx, m_terrain->get_width());
	endy = std::min(endy, m_terrain->get_height()); 
	
	for (int x = startx; x <= endx; x++) {
		for (int y = starty; y <= endy; y++) {
			int type = m_terrain->get(x, y);
			
			bool edge = x == startx || x == endx || y == starty || y == endy;
			
			if ((type  & terrain_component::OPAQUE) || edge) {
				bool surrounded = true;

				for (int i = 0; i < 9; i++) {
					int a = i % 3 - 1;
					int b = i / 3 - 1;
					
					if (i == 4) continue;
					if (!(m_terrain->get(x + a, y + b) & terrain_component::OPAQUE)) surrounded = false;
				}

				if (surrounded) continue;
				
				int no = (x - light_pos.get_x() > 0) + 2 * (y - light_pos.get_y() > 0);
				
				for (int i = 0; i < 4; i++) {
					if (i == no) continue;
					
					int a = i % 2;
					int b = i / 2;
					
					float dx = x + a - light_pos.get_x();
					float dy = y + b - light_pos.get_y();
					
					// if (abs(dx) < 0.2 || abs(dy) < 0.2) continue;
					
					float dir = atan2(dy, dx);
					
					if (std::count(duplicates.begin(), duplicates.end(), dir))
						continue;
					
					duplicates.push_back(dir);
					
					loli::vec2 hit0 = raycast(light_pos, dir - 0.001, radius);
					loli::vec2 hit1 = raycast(light_pos, dir + 0.001, radius);
					
					rays.push_back(ray(dir - 0.001f, hit0));
					rays.push_back(ray(dir + 0.001f, hit1));
					
				}
			}
		}
	}
	
	std::sort(rays.begin(), rays.end(),
	[] (std::pair<float, loli::vec2> l, std::pair<float, loli::vec2> r) {
		return l.first < r.first;
	});
	
	loli::vec2 uv_size = loli::vec2(1.0 / 8.0f, 1.0 / 8.0f);

	std::vector<loli::vertex> vertices;
	
	float z = 0.0f;
	
	vertices.push_back(loli::vertex(loli::vec3(light_pos, 0.0), loli::vec3(0.0, 0.0, 1.0), loli::vec2(2.0, 7.0) * uv_size));
	
	for (int i = 0; i < rays.size(); i++) {
		loli::vec3 pos0 = loli::vec3(rays[i].second, z);
		loli::vec3 pos1 = loli::vec3(rays[(i + 1) % rays.size()].second, z);
		
		vertices.push_back(loli::vertex(pos0, loli::vec3(0.0, 0.0, 1.0), loli::vec2(2.0, 7.0) * uv_size));
		vertices.push_back(loli::vertex(pos1, loli::vec3(0.0, 0.0, 1.0), loli::vec2(2.0, 7.0) * uv_size));
	}
	
	m_shadow_size = vertices.size();
	m_shadow_mesh->sub_vertices(vertices.data(), 0, vertices.size());
}
