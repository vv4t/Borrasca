#include "bat_component.hpp"

#include "health.hpp"
#include "entity_type.hpp"

void bat_component::start() {
	m_player = get_engine().get_entity(2);
	m_sprite = get_component<sprite_render*>(2);
	m_rigid = get_component<rigid_body*>(0);
	m_director = get_engine().get_entity(5)->get_component<director*>(0);
	
	m_sprite->get_uv_offset().set_y(4);
	
	get_transform().scale(loli::vec3(0.7f, 0.7f, 1.0f));
	
	m_bat_pos = get_transform().get_pos();
}

void bat_component::tick() {
	loli::vec3 dir = m_player->get_transform().get_pos() - get_transform().get_pos();
	
	if (dir.length() > 30) {
		get_parent()->remove();
		return;
	}
	
	m_rigid->projected_accelerate(dir.normalize(), 1, 1.5);
	
	if (get_ticks() % 5 == 0)
		m_rigid->projected_accelerate(loli::vec3(rand() % 10 - 5, rand () % 10 - 5).normalize(), 5, 5);
	
	m_sprite->get_uv_offset().set_x(get_ticks() % 10 > 5);
}

void bat_component::remove() {
	m_director->remove(get_parent());
}

void bat_component::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_PLAYER) {
		if (get_ticks() % 40 == 0) {
			e->get_component<health*>(5)->remove_hp(2);
		}
	}
}