#include "rigid_body.hpp"

float rigid_body::time_step = 1.0f / 60.0f;

void rigid_body::tick() {
	if (m_grounded)
		friction();
	
	loli::vec3 pos = get_transform().get_pos();
	
	loli::vec3 new_pos = pos + m_velocity;
	
	get_transform().set_pos(new_pos);
}

void rigid_body::friction() {
	float speed = m_velocity.length();
	
	if (speed != 0) {
		float drop = speed * m_drag * time_step;
		
		m_velocity *= lmax(speed - drop, 0) / speed;
	}
}

void rigid_body::accelerate(loli::vec3 dir, float accel, float max_vel) {
	float speed = accel;
	
	if ((m_velocity + dir * speed).length() > max_vel * time_step)
		speed = max_vel * time_step - m_velocity.length();
	
	add_force(dir * speed);
}

void rigid_body::projected_accelerate(loli::vec3 dir, float accel, float max_vel) {
	float projvel = m_velocity.dot(dir);
	float speed = accel * time_step;
	
	float addspeed = max_vel * time_step - projvel;
	
	if (addspeed < 0) return;
	
	if (speed > addspeed)
		speed = addspeed;
	
	add_force(dir * speed);
}

void rigid_body::add_force(loli::vec3 f) {
	m_velocity += f;
}

void rigid_body::set_velocity(loli::vec3 v) {
	m_velocity = v;
}

loli::vec3 rigid_body::get_velocity() {
	return m_velocity;
}

void rigid_body::set_drag(float f) {
	m_drag = f;
}

float rigid_body::get_drag() {
	return m_drag;
}

void rigid_body::is_grounded(bool b) {
	m_grounded = b;
}