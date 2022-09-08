#include "emitter_particle.hpp"

emitter_particle::emitter_particle(float speed, int life) : particle_system(10) {
	m_speed = speed;
	m_life = life;
}

void emitter_particle::p_init(particle* p) {
	p->m_pos = loli::vec3().set_z(0.1);
	p->m_vel = (loli::vec3(rand() % 10 - 5, rand() % 10 + 10).normalize() * m_speed).rotate(get_cam().get_transform().get_rot());
	p->m_end = get_ticks() + rand() % m_life + 5;
}

void emitter_particle::p_move(particle* p) {
	p->m_vel -= loli::vec3(0, 0.01).rotate(get_cam().get_transform().get_rot());
	p->m_pos += p->m_vel;
}

void emitter_particle::tick() {
	if (m_hide)
		return;
	
	particle_system::tick();
}

void emitter_particle::render() {
	if (m_hide)
		return;
	
	particle_system::render();
}

void emitter_particle::hide(bool b) {
	m_hide = b;
}