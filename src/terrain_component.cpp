#include "terrain_component.hpp"

#include <vector>
#include <algorithm>

#include "sprite_render.hpp"
#include "vertex.hpp"
#include "math3d.hpp"
#include "entity_type.hpp"
#include "pushable.hpp"
#include "rock_component.hpp"
#include "crate_component.hpp"
#include "terrain_collider.hpp"
#include "generator.hpp"
#include "director.hpp"
#include "droppable.hpp"

loli::vec2 uv_size = loli::vec2(1.0 / 16.0f, 1.0f / 16.0f);
loli::vec3 up = loli::vec3(0, 0, 1);

void terrain_component::add_wall(loli::vec3 p0, loli::vec3 p1, loli::vec2 tex, int shift) {
	for (int i = 0; i < 6; i++)
		m_indices.push_back(m_vertices.size() + i % 3 + (i / 3));
	
	for (int i = 0; i < 4; i++) {
		int a = i % 2;
		int b = i / 2;
		
		loli::vec3 pos = p0 + p1 * a + loli::vec3(0, 0, b);
		loli::vec3 n = p1.cross(up);
		loli::vec2 uv = (tex + loli::vec2(0.5, 0.5) + (loli::vec2(a * 2 - 1, (1 - b) * 2 - 1) * 0.5).rotate((float) shift * M_PI / 180.0 * 90)) * uv_size;
		
		m_vertices.push_back(loli::vertex(pos, n, uv));
	}
}

void terrain_component::add_wall(loli::vec3 pos, loli::vec2 tex, int shift) {
	float rot = shift * M_PI / 2.0f;
	
	loli::vec3 t0 = pos + loli::vec3(0.5, 0.5) + loli::vec3(-0.5, 0.0).rotate(rot);
	loli::vec3 t1 = loli::vec3(1.0, 0.0).rotate(rot);
	
	for (int i = 0; i < 6; i++)
		m_indices.push_back(m_vertices.size() + i % 3 + (i / 3));
	
	for (int i = 0; i < 4; i++) {
		int a = i % 2;
		int b = i / 2;
		
		loli::vec3 pos = t0 + t1 * a + loli::vec3(0, 0, b);
		loli::vec2 uv = (tex + loli::vec2(a, 1 - b)) * uv_size;
		
		m_vertices.push_back(loli::vertex(pos, up, uv));
	}
}

void terrain_component::add_tile(loli::vec3 t, loli::vec2 tex, int shift) {
	for (int i = 0; i < 6; i++)
		m_indices.push_back(m_vertices.size() + i % 3 + (i / 3));
	
	for (int i = 0; i < 4; i++) {
		int a = i % 2;
		int b = i / 2;
		
		loli::vec3 pos = t + loli::vec3(a, b);
		loli::vec2 uv = (tex + loli::vec2(0.5, 0.5) + (loli::vec2(a * 2 - 1, (1 - b) * 2 - 1) * 0.5).rotate((float) shift * M_PI / 180.0 * 90)) * uv_size;
		
		m_vertices.push_back(loli::vertex(pos, up, uv));
	}
}

void terrain_component::load_map(loli::bitmap* bmp) {
	map_w = bmp->get_width();
	map_h = bmp->get_height();
	
	map_chunk_w = bmp->get_width() / chunk_w;
	map_chunk_h = bmp->get_height() / chunk_h;
	
	m_map = (unsigned char*) malloc(map_w * map_h);
	
	for (int i = 0; i < map_w * map_h; i++) {
		int r = bmp->get(i * 4 + 0);
		int g = bmp->get(i * 4 + 1);
		int b = bmp->get(i * 4 + 2);
		
		m_map[i] = 0;
	}
	
	m_chunk_ptr = (int*) malloc((map_chunk_w * map_chunk_h + 1) * sizeof(int));
	director* _director = get_engine().get_entity(5)->get_component<director*>(0);
	
	for (int y = 0; y < map_chunk_h; y++) {
		for (int x = 0; x < map_chunk_w; x++) {
			m_chunk_ptr[x + y * map_chunk_w] = m_indices.size();
			
			for (int yc = 0; yc < chunk_h; yc++) {
				for (int xc = 0; xc < chunk_w; xc++) {
					loli::vec3 t = loli::vec3(xc + x * chunk_w, yc + y * chunk_h, 0.0f);
					
					int i = (int) t.get_x() + (int) t.get_y() * map_w;
					
					int r = bmp->get(i * 4 + 0);
					int g = bmp->get(i * 4 + 1);
					int b = bmp->get(i * 4 + 2);
					
					int col = r << 16 | g << 8 | b;
					
					if (col == 0xff99ff) {
						m_map[i] = 0;
						continue;
					}
					
					// WALL
					if (col == 0xffffff) {
						m_map[i] = terrain_component::SOLID | terrain_component::OPAQUE;
						
						loli::vec2 uv = loli::vec2(1, 7);
						
						int s = rand() % 4;
						
						if (!(get((int) t.get_x(), (int) t.get_y() - 1) & terrain_component::OPAQUE)) add_wall(t + loli::vec3(0, 0), loli::vec3(1, 0), uv, s);
						if (!(get((int) t.get_x() + 1, (int) t.get_y()) & terrain_component::OPAQUE)) add_wall(t + loli::vec3(1, 0), loli::vec3(0, 1), uv, s);
						if (!(get((int) t.get_x(), (int) t.get_y() + 1) & terrain_component::OPAQUE)) add_wall(t + loli::vec3(1, 1), loli::vec3(-1, 0), uv, s);
						if (!(get((int) t.get_x() - 1, (int) t.get_y()) & terrain_component::OPAQUE)) add_wall(t + loli::vec3(0, 1), loli::vec3(0, -1), uv, s);
						
						add_tile(t + loli::vec3(0, 0, 1), loli::vec2(1, 7), 0);
					} else if (col == 0x643232) { // elevator wall
						loli::vec2 uv = loli::vec2(8, 7);
						loli::vec2 uv0 = loli::vec2(1, 7);
						
						float b = 0.2;
						
						if (!(get((int) t.get_x(), (int) t.get_y() - 1) & terrain_component::OPAQUE)) {
							add_wall(t + loli::vec3(0, 0), loli::vec3(1, 0), uv0, 0);
							add_wall(t + loli::vec3(0, -b), loli::vec3(1, 0), uv, 0);
						}
						
						if (!(get((int) t.get_x() + 1, (int) t.get_y()) & terrain_component::OPAQUE)) {
							add_wall(t + loli::vec3(1, 0), loli::vec3(0, 1), uv0, 0);
							add_wall(t + loli::vec3(1 + b, 0), loli::vec3(0, 1), uv, 0);
						}
						
						if (!(get((int) t.get_x(), (int) t.get_y() + 1) & terrain_component::OPAQUE)) {
							add_wall(t + loli::vec3(1, 1), loli::vec3(-1, 0), uv0, 0);
							add_wall(t + loli::vec3(1, 1 + b), loli::vec3(-1, 0), uv, 0);
						}
						
						if (!(get((int) t.get_x() - 1, (int) t.get_y()) & terrain_component::OPAQUE)) {
							add_wall(t + loli::vec3(0, 1), loli::vec3(0, -1), uv0, 0);
							add_wall(t + loli::vec3(-b, 1), loli::vec3(0, -1), uv, 0);
						}
						
						add_tile(t + loli::vec3(0, 0, 1), loli::vec2(1, 7), 0);
					} else if (col == 0x643245) { // elevator floor
						add_tile(t + loli::vec3(0, 0, 0.1), loli::vec2(9, 7), 0);
					} else if (col == 0x00d1ff) {
						_director->add_boss(t);
					} else if (col == 0x4600ff) { // generator
						loli::entity* e = get_engine().add_entity();
						
						e->add_component(new rigid_body());
						e->add_component(new generator());
						e->add_component(new sprite_render());
						e->add_component(new circle_collider(1.0));
						e->set_type(ENTITY_GENERATOR);
						e->start();
						
						e->get_transform().set_pos(t);
						e->get_transform().set_scale(loli::vec3(2, 2, 1));
					} else if (col == 0xff8b3f) { // gas
						loli::entity* e = get_engine().add_entity();
						e->add_component(new rigid_body());
						e->add_component(new droppable(4));
						e->add_component(new sprite_render());
						e->add_component(new circle_collider(0.5));
						
						e->set_type(ENTITY_DROPPABLE);
						e->start();
						
						e->get_transform().translate(t + loli::vec3(0.5, 0.5));
					} else if (col == 0x500000) { // WATER
						add_tile(t + loli::vec3(0, 0, 1), loli::vec2(1, 7), 0);
						add_tile(t + loli::vec3(0, 0.0), loli::vec2(2, 7), rand() % 4);
						
						continue;
					}else if (col == 0xff00ff) { // VOID
						m_map[i] = terrain_component::SOLID | terrain_component::OPAQUE;
						add_tile(t + loli::vec3(0, 0, 1), loli::vec2(7, 7), 0);
					} else if (col == 0xbabb31) { // BARREL
						m_map[i] = terrain_component::SOLID;
						loli::entity* e = get_engine().add_entity();
						e->add_component(new sprite_render(loli::vec2(2, 5)));
						e->start();
						
						e->get_transform().set_pos(t + loli::vec3(0.5, 0.5));
					} else if (col == 0x797979) { // ROCK
						loli::entity* e = get_engine().add_entity();
						
						e->add_component(new rigid_body());
						e->add_component(new sprite_render(loli::vec2(3, 5)));
						e->add_component(new circle_collider(0.5));
						e->add_component(new rock_component());
						e->start();
						
						e->get_transform().set_pos(t + loli::vec3(0.5, 0.5));
						e->get_transform().set_scale(loli::vec3((rand() % 2 == 1 ? -1 : 1), 1, 1));
					} else if (col == 0x303030) { // PILLAR
						loli::entity* e = get_engine().add_entity();
						
						e->add_component(new rigid_body());
						e->add_component(new sprite_render(loli::vec2(5, 5)));
						e->add_component(new circle_collider(0.5));
						e->add_component(new rock_component());
						e->start();
						
						e->get_transform().set_pos(t + loli::vec3(0.5, 0.5));
						e->get_transform().set_scale(loli::vec3((rand() % 2 == 1 ? -1 : 1), 1, 1));
					} else if (col == 0x00ffff) { // WATER
						m_map[i] = terrain_component::LIQUID;
						add_tile(t + loli::vec3(0, 0.0), loli::vec2(2, 7), rand() % 4);
						
						if (rand() % 5 == 3) {
							_director->add_bat(t);
						}
						
						continue;
					} else if (col == 0x69ff69) { // BOX
						loli::entity* e = get_engine().add_entity();
						
						e->add_component(new rigid_body());
						e->add_component(new sprite_render(loli::vec2(4, 5)));
						e->add_component(new circle_collider(0.5));
						e->add_component(new crate_component());
						e->get_transform().set_pos(t + loli::vec3(0.5, 0.5));
						e->start();
					} else if (col == 0xc0ff33) {
						_director->add_spawn(t);
					} else if (col == 0x0000ff) { // PLAYER
						get_engine().get_entity(2)->get_transform().set_pos(t);
					} else {
						if (r == 255) // RAIL
							add_tile(t + loli::vec3(0, 0.1), loli::vec2(3, 7), b / 64);
						else if (r == 100) // CORNER
							add_tile(t + loli::vec3(0, 0.1), loli::vec2(4, 7), b / 64);
						
						if (g == 255) // SUPPORT BEAM
							add_wall(t, loli::vec2(0, 6), b / 64);
						else if (g == 100) // SUPPORT
							add_wall(t, loli::vec2(1, 6), (b + 2) % 4 / 64);
						else if (g == 50 || g == 80) { //FENCE
							m_map[i] = terrain_component::SOLID;
							add_wall(t, loli::vec2(2, 6), b / 64);
						}
					}
					
					//DEFAULT
					if (!(m_map[i] & terrain_component::OPAQUE)) {
						int x = (rand() % 10 == 5) * 5;
						
						if (g == 80)
							x = 2;
						
						add_tile(t, loli::vec2(x, 7), rand() % 4);
					}
				}
			}
		}
	}
	
	m_chunk_ptr[map_chunk_w * map_chunk_h] = m_indices.size();
	m_mesh = get_render().add_mesh();
	m_mesh->init(m_vertices.data(), m_vertices.size());
	m_mesh->index(m_indices.data(), m_indices.size());
	
	m_vertices.clear();
	m_indices.clear();
}

void terrain_component::tick() {
	if (get_ticks() % (60 * 11) == 0) {
		std::cout << "cave sound" << std::endl;
		// get_engine().get_sound_engine().play2D("assets/sound/cave.wav");
	}
	
	float chunk_x = get_cam().get_transform().get_pos().get_x() / (float) chunk_w;
	float chunk_y = get_cam().get_transform().get_pos().get_y() / (float) chunk_h;
	
	int active_x = (chunk_x - floor(chunk_x) > 0.5) ? +1 : -1;
	int active_y = (chunk_y - floor(chunk_y) > 0.5) ? +1 : -1;
	
	for (int i = 0; i < 4; i++) {
		int x = (int) chunk_x + active_x * (i % 2);
		int y = (int) chunk_y + active_y * (i / 2);
		
		if (x >= 0 && y >= 0 && x < map_chunk_w && y < map_chunk_h)
			m_active_chunks[i] = x + y * map_chunk_w;
		else m_active_chunks[i] = -1;
	}
}

void terrain_component::render() {
	get_render().get_shader()->uniform_vec3("u_color", loli::vec3(1, 1, 1));
	get_render().get_shader()->uniform_vec2("u_uv_size", loli::vec2(1, 1));
	get_render().get_shader()->uniform_mat4("u_transform", get_cam().to_projected_view(get_transform().get_mat()));
	get_render().get_shader()->uniform_mat4("u_model", get_transform().get_mat());
	get_render().get_shader()->uniform_vec2("u_uv_offset", loli::vec2());
	get_render().get_shader()->uniform_float("u_clamp", 0.0);
	get_render().bind_mesh(m_mesh);
	
	float z = get_cam().get_proj().get(6);
	get_cam().get_proj().set(6, 0.0f);
	
	get_render().get_shader()->uniform_mat4("u_tilemat", get_cam().to_projected_view(get_transform().get_mat()));
	
	get_cam().get_proj().set(6, z);
	
	for (int i = 0; i < 4; i++) {
		int chunk = m_active_chunks[i];
		
		if (chunk < 0) continue;
		
		int start = m_chunk_ptr[chunk];
		int size = m_chunk_ptr[chunk + 1] - start;
		
		get_render().draw_elements(start, size);
	}
}

unsigned char terrain_component::get(int x, int y) {
	if (x < 0 || y < 0 || x >= map_w || y >= map_h)
		return 0;
	
	return m_map[x + y * map_w];
}

int terrain_component::get_width() {
	return map_w;
}

int terrain_component::get_height() {
	return map_h;
}
