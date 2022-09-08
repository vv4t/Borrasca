#include "break_particle.hpp"

void break_particle::p_init(particle* p) {
	p->m_pos = loli::vec3().set_z(0.2);
	p->m_vel = (loli::vec3(rand() % 10 - 5, rand() % 10 - 5).normalize() * ((rand() % 10) / 50.0 + 0.05));
	p->m_end = get_ticks() + 60;
}

void break_particle::p_move(particle* p) {
	p->m_vel *= 0.90;
	p->m_pos += p->m_vel;
}

void break_particle::start() {
	particle_system::start();
	m_end = get_ticks() + 60;
}

void break_particle::tick() {
	if (get_ticks() > m_end) {
		get_parent()->remove();
		return;
	}
	
	particle_system::tick();
}