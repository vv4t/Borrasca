#include "transform.hpp"

loli::transform::transform () {
	m_pos = loli::vec3(0.0f, 0.0f, 0.0f);
	m_scale = loli::vec3(1.0f, 1.0f, 1.0f);
	m_rot = 0.0;
	
	m_transform.identity();
}

void loli::transform::translate(loli::vec3 v) {
	m_pos += v;
	m_update = true;
}

void loli::transform::scale(loli::vec3 v) {
	m_scale *= v;
	m_update = true;
}

void loli::transform::rotate(float angle) {
	m_rot += angle;
	m_update = true;
}

void loli::transform::set_pos(loli::vec3 v) {
	m_pos = v;
	m_update = true;
}

void loli::transform::set_scale(loli::vec3 v) {
	m_scale = v;
	m_update = true;
}

void loli::transform::set_rot(float angle) {
	m_rot = angle;
	m_update = true;
}

void loli::transform::mat_update() {
	loli::mat4 mat = loli::mat4().scale(m_scale);
	m_transform = mat;
	
	mat.rotate_z(m_rot);
	m_transform = mat * m_transform;
	
	mat.translate(m_pos);
	m_transform = mat * m_transform;
}

loli::mat4 loli::transform::get_mat() {
	if (m_update) {
		mat_update();
		m_update = false;
	}
	
	return m_transform;
}

float loli::transform::get_rot() {
	return m_rot;
}

loli::vec3 loli::transform::get_pos() {
	return m_pos;
}

loli::vec3 loli::transform::get_scale() {
	return m_scale;
}