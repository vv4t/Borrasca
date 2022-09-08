#include "particle_system.hpp"

#include <vector>

particle_system::particle_system(int count) {
	m_count = count;
}

void particle_system::remove() {
	get_render().remove_mesh(m_mesh);
}

void particle_system::start() {
	m_particles.alloc_block(m_count);
	
	m_mesh = get_render().add_mesh();
	m_mesh->init(nullptr, m_count * 4);
	m_mesh->index(nullptr, m_count * 6);
	
	for (int i = 0; i < m_count; i++)
		m_particles.get(i)->m_end = 0;
}

void particle_system::tick() {
	std::vector<loli::vertex> vertices;
	std::vector<unsigned int> indices;
	
	loli::vec3 up = loli::vec3(0, 0, 1);
	loli::vec2 uv = loli::vec2(1 / 16.0, 1 / 16.0);
	
	for (int i = 0; i < m_count; i++) {
		particle* p = m_particles.get(i);
		
		if (get_ticks() > p->m_end) {
			p->m_start_pos = get_transform().get_pos();
			p_init(p);
		}
		
		p_move(p);
	
		for (int j = 0; j < 6; j++)
			indices.push_back(vertices.size() + (j % 3) + (j / 3));
		
		for (int j = 0; j < 4; j++) {
			int a = j % 2;
			int b = j / 2;
			
			loli::vec3 pos = (p->m_pos - get_transform().get_pos() + p->m_start_pos + loli::vec3(a, b, 0) * p->m_pos.get_z());
			
			vertices.push_back(loli::vertex(pos, up, (loli::vec2(6, 7) + loli::vec2(a, b)) * uv));
		}
	}
	
	m_mesh->sub_vertices(vertices.data(), 0, vertices.size());
	m_mesh->sub_indices(indices.data(), 0, indices.size());
}

void particle_system::set_color(loli::vec3 col) {
	m_color = col;
}

void particle_system::render() {
	float z = get_cam().get_proj().get(6);
	get_cam().get_proj().set(6, 0.0f);
	
	loli::mat4 m = get_cam().to_projected_view(loli::mat4().translate(get_transform().get_pos()));
	
	if (abs(m.get(3)) < 1.0 || abs(m.get(7)) < 1.0f) {
		get_render().get_shader()->uniform_vec3("u_color", m_color);
		get_render().get_shader()->uniform_vec2("u_uv_offset", loli::vec2(0, 0));
		get_render().get_shader()->uniform_mat4("u_model", get_transform().get_mat());
		get_render().get_shader()->uniform_mat4("u_transform", m);
		get_render().get_shader()->uniform_mat4("u_light_mat", m);
		get_render().get_shader()->uniform_float("u_clamp", 1.0);
		
		get_render().bind_mesh(m_mesh);
		get_render().draw_elements(0, m_count * 6);
	}
	
	get_cam().get_proj().set(6, z);
}