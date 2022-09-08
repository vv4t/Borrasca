#include "sprite_render.hpp"

sprite_render::sprite_render() {
	m_uv_size = loli::vec2(1, 1);
	m_rot = false;
}

sprite_render::sprite_render(loli::vec2 offset) {
	m_rot = false;
	m_uv_offset = offset;
	m_uv_size = loli::vec2(1, 1);
}

void sprite_render::tick() {
	if (!m_rot)
		get_transform().set_rot(get_cam().get_transform().get_rot());
}

void sprite_render::render() {
	loli::vec2 uv_size = loli::vec2(1.0f / 16.0f, 1.0f / 16.0f);
	
	float z = get_cam().get_proj().get(6);
	get_cam().get_proj().set(6, 0.0f);
	
	/*
		0  1  2  3
		4  5  6  7
		8  9  10 11
		12 13 14 15
	*/
	
	get_transform().translate(loli::vec3(0, 0.25).rotate(get_cam().get_transform().get_rot()));
	
	loli::mat4 model = get_transform().get_mat();
	loli::mat4 m = get_cam().to_projected_view(model);
	
	if (abs(m.get(3)) < 1.0 || abs(m.get(7)) < 1.0f) {
		get_render().get_shader()->uniform_vec3("u_color", loli::vec3(1, 1, 1));
		get_render().get_shader()->uniform_vec2("u_uv_size", m_uv_size);
		get_render().get_shader()->uniform_vec2("u_uv_offset", m_uv_offset * uv_size);
		get_render().get_shader()->uniform_mat4("u_model", model);
		get_render().get_shader()->uniform_mat4("u_transform", m);
		get_render().get_shader()->uniform_float("u_clamp", 1.0);
		
		loli::mat4 light_mat = get_cam().to_projected_view(model);
		
		light_mat.set(5, 0.0);
		
		get_render().get_shader()->uniform_mat4("u_light_mat", light_mat);
		
		get_render().bind_mesh(0);
		get_render().draw_elements(0, 6);
	}
	
	get_transform().translate(loli::vec3(0, -0.25).rotate(get_cam().get_transform().get_rot()));
	
	get_cam().get_proj().set(6, z);
}

loli::vec2& sprite_render::get_uv_offset() {
	return m_uv_offset;
}

loli::vec2& sprite_render::get_uv_size() {
	return m_uv_size;
}

void sprite_render::is_rotate(bool rotate) {
	m_rot = rotate;
}