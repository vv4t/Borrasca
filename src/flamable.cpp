#include "flamable.hpp"

#include "entity_type.hpp"

void flamable::start() {
	m_emitter = get_component<emitter_particle*>(7);
	
	m_light = get_render().get_light().add_light(get_transform().get_pos(), loli::vec3(1.0, 0.8, 0.6), 2.0, 0.0, M_PI * 2);
	m_light->enable_shadow(false);
}

void flamable::tick() {
	if (get_ticks() < m_burn_end) {
		m_emitter->hide(false);
		m_light->set_pos(get_transform().get_pos());
		m_light->set_intensity(cos(get_ticks() / 2.0f) * 0.25 + 2.0);
	} else {
		m_emitter->hide(true);
		m_light->set_intensity(0);
	}
}

void flamable::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_FLASHLIGHT) {
		m_burn_end = get_ticks() + 30;
	}
}

void flamable::remove() {
	get_render().get_light().remove_light(m_light);
}