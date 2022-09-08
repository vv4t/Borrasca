#include "light_manager.hpp"

#include <string.h>

loli::light::light(loli::vec3 pos, loli::vec3 col, float intensity, float dir, float angle) {
	m_pos = pos;
	m_col = col;
	m_intensity = intensity;
	m_dir = dir;
	m_angle = angle;
}

void loli::light::set_pos(vec3 v) {
	m_pos = v;
}

void loli::light::set_col(vec3 v) {
	m_col = v;
}

void loli::light::set_dir(float f) {
	m_dir = f;
}

void loli::light::set_angle(float f) {
	m_angle = f;
}

void loli::light::set_intensity(float f) {
	m_intensity = f;
}

loli::vec3 loli::light::get_pos() {
	return m_pos;
}

float loli::light::get_dir() {
	return m_dir;
}

float loli::light::get_angle() {
	return m_angle;
}

float loli::light::get_intensity() {
	return m_intensity;
}

void loli::light::enable_shadow(bool b) {
	m_shadow = b;
}

bool loli::light::is_shadow() {
	return m_shadow;
}

loli::light_manager::light_manager(loli::render_engine* render, int size) {
	m_render = render;
	m_light_size = size;
	m_light_count = 0;
	
	m_light_pool.alloc_block(size);
	m_ubo = render->add_ubo(16 + size * sizeof(loli::light), 0);
	m_block = (char*) malloc(16 + size * sizeof(loli::light));
}

loli::light* loli::light_manager::add_light(loli::vec3 pos, loli::vec3 col, float intensity, float dir, float angle) {
	loli::light* l = new (m_light_pool.alloc()) light(pos, col, intensity, dir, angle);
	
	update_lights();
	
	return l;
}

loli::light* loli::light_manager::get_light(int id) {
	return m_light_pool.get(id);
}

void loli::light_manager::update_light(int id) {
	memcpy(m_block + 16 + id * sizeof(loli::light), m_light_pool.get(id), sizeof(loli::light));
	m_ubo->sub_data(m_block + 16 + id * sizeof(loli::light), 16 + id * sizeof(loli::light), sizeof(loli::light));
}

void loli::light_manager::update_lights() {
	float ambience = 0.1;
	int count = m_light_pool.len();
	
	memcpy(m_block, &count, sizeof(int));
	memcpy(m_block + 4, &ambience, sizeof(float));
	
	memset(m_block + 8, 0, 8);
	memset(m_block + 16, 0, m_light_size * sizeof(loli::light));
	
	for (int i = 0; i < count; i++) {
		if (m_light_pool.is_alloc(i))
			memcpy(m_block + 16 + i * sizeof(loli::light), m_light_pool.get(i), sizeof(loli::light));
	}
	
	m_ubo->sub_data(m_block, 0, 16 + count * sizeof(loli::light));
}

void loli::light_manager::remove_light(loli::light* light) {
	m_light_pool.remove(light);
}