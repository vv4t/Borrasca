#include "flare_component.hpp"

#include "entity_type.hpp"
#include "health.hpp"

flare_component::flare_component(loli::vec3 dir, float speed, int life) {
	m_dir = dir;
	m_speed = speed;
	m_life = life;
}

void flare_component::start() {
	m_start = get_ticks();
	m_end = get_ticks() + m_life;
	m_rigid = get_component<rigid_body*>(0);
	m_sprite = get_component<sprite_render*>(1);
	m_rigid->projected_accelerate(m_dir * m_speed, 10, 10);
	
	m_sprite->get_uv_offset().set_x(7);
	m_sprite->get_uv_offset().set_y(8);
	
	m_rigid->set_drag(7.0);
	
	m_light = get_render().get_light().add_light(get_transform().get_pos(), loli::vec3(1.0, 0.5, 0.5), 3.0, 0.0, M_PI * 2);
	m_light->enable_shadow(false);
	
	get_transform().set_scale(loli::vec3(0.7, 0.7, 1.0));
}

void flare_component::tick() {
	if (get_ticks() > m_end) {
		get_parent()->remove();
		return;
	}
	
	if (m_rigid->get_velocity().length() < 0.05 && !m_landed)
		m_landed = true;
	
	m_light->set_pos(get_transform().get_pos());
	m_light->set_intensity(cos(get_ticks() / 2.0f) * 0.25 + (1 - (float) (get_ticks() - m_start) / (float) (m_end - m_start)) * 5.0f);
	
	m_rigid->friction();
}

void flare_component::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_GHOST || e->get_type() == ENTITY_BOSS) {
		health* hp;
		if (e->get_type() == ENTITY_GHOST)
			hp = e->get_component<health*>(6);
		if (e->get_type() == ENTITY_BOSS)
			hp = e->get_component<health*>(4);
		
		if (!m_landed) {
			hp->remove_hp(50);
			
			if (hp->get_health() > 0)
				m_rigid->set_velocity(loli::vec3());
		} else {
			if (get_ticks() % 30 == 0)
				hp->remove_hp(5);
		}
	}
	
	if (e->get_type() == ENTITY_PLAYER) {
		
	}
}

void flare_component::remove() {
	get_render().get_light().remove_light(m_light);
}