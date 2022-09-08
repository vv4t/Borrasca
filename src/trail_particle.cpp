#include "trail_particle.hpp"

trail_particle::trail_particle(rigid_body* rigid, int count, int reset, float speed) : particle_system(count) {
	m_rigid = rigid;
	
	m_reset = reset;
	m_speed = speed;
}

void trail_particle::p_init(particle* p) {
	loli::vec3 rvec = loli::vec3(rand() % 10 - 5, rand() % 10 - 5).normalize();
	
	p->m_pos = rvec * 0.1;
	p->m_vel = (rvec * 0.04 + m_rigid->get_velocity().normalize() * -m_speed).set_z(0.1);
	p->m_end = get_ticks() + m_reset + (rand() % m_reset);
}

void trail_particle::p_move(particle* p) {
	p->m_vel *= 0.90;
	p->m_pos = (p->m_pos + p->m_vel).set_z(0.1);
}