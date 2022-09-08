#include "render_engine.hpp"

#include <iostream>
#include <GL/glew.h>

loli::render_engine::render_engine() {
	glewExperimental = 1;
	
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialise GLFW" << std::endl;
		return;
	}
	
	m_mesh_pool.alloc_block(50);
	m_shader_pool.alloc_block(10);
	m_texture_pool.alloc_block(10);
	m_ubo_pool.alloc_block(10);
	m_fbo_pool.alloc_block(10);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	
	m_lights = new loli::light_manager(this, 30);
}

loli::render_engine::~render_engine() {
	
}

void loli::render_engine::viewport(int x, int y, int w, int h) {
	glViewport(x, y, w, h);
}

void loli::render_engine::clear_color(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void loli::render_engine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

loli::mesh* loli::render_engine::add_mesh() {
	return new (m_mesh_pool.alloc()) mesh();
}

loli::shader* loli::render_engine::add_shader(char* vs, char* fs) {
	return new (m_shader_pool.alloc()) shader(vs, fs);
}

loli::texture* loli::render_engine::add_texture(loli::bitmap* bmp) {
	return new (m_texture_pool.alloc()) texture(bmp);
}

loli::uniform_buffer* loli::render_engine::add_ubo(unsigned int size, unsigned int id) {
	return new (m_ubo_pool.alloc()) uniform_buffer(size, id);
}

loli::frame_buffer* loli::render_engine::add_fbo(unsigned int width, unsigned int height) {
	return new (m_fbo_pool.alloc()) frame_buffer(width, height);
}

void loli::render_engine::remove_mesh(loli::mesh* mesh) {
	m_mesh_pool.remove(mesh);
}

void loli::render_engine::bind_mesh(int id) {
	if (m_mesh_id == m_mesh_pool.get(id))
		return;
	
	m_mesh_pool.get(id)->bind();
	m_mesh_id = m_mesh_pool.get(id);
}

void loli::render_engine::bind_shader(int id) {
	if (m_shader_id == m_shader_pool.get(id))
		return;
	
	m_shader_pool.get(id)->bind();
	m_shader_id = m_shader_pool.get(id);
}

void loli::render_engine::bind_texture(int id, int sampler) {
	m_texture_pool.get(id)->bind(sampler); 
}

void loli::render_engine::bind_mesh(loli::mesh* mesh) {
	if (m_mesh_id == mesh)
		return;
	
	m_mesh_id = mesh;
	m_mesh_id->bind();
}

void loli::render_engine::bind_shader(loli::shader* shader) {
	if (m_shader_id == shader)
		return;
	
	m_shader_id = shader;
	m_shader_id->bind();
}

void loli::render_engine::bind_texture(loli::texture* texture, int sampler) {
	texture->bind(sampler); 
}

void loli::render_engine::draw_arrays(GLenum mode, int start, int size) {
	glDrawArrays(mode, start, size);
}

void loli::render_engine::draw_elements(int start, int size) {
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*) (start * sizeof(int)));
}

loli::mesh* loli::render_engine::get_mesh(unsigned int id) {
	return m_mesh_pool.get(id);
}

loli::shader* loli::render_engine::get_shader(unsigned int id) {
	return m_shader_pool.get(id);
}

loli::texture* loli::render_engine::get_texture(unsigned int id) {
	return m_texture_pool.get(id);
}

loli::mesh* loli::render_engine::get_mesh() {
	return m_mesh_id;
}

loli::shader* loli::render_engine::get_shader() {
	return m_shader_id;
}

loli::camera& loli::render_engine::get_cam() {
	return m_cam;
}

loli::light_manager& loli::render_engine::get_light() {
	return *m_lights;
}

loli::vec2 screenscale = loli::vec2(1.0 / 80.0, 1.0 / 60.0);

void loli::render_engine::gui_img(int sampler, loli::vec2 pos, loli::vec2 size, loli::vec2 uv_pos, loli::vec2 uv_size) {
	bind_texture(sampler, 0);
	
	get_shader()->uniform_vec2("u_uv_pos", uv_pos);
	get_shader()->uniform_vec2("u_uv_size", uv_size);
	
	get_shader()->uniform_vec2("u_pos", pos * screenscale);
	get_shader()->uniform_vec2("u_size", size * screenscale);
	
	draw_elements(0, 6);
}