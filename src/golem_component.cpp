#include "golem_component.hpp"

#include "break_particle.hpp"
#include "ghost_projectile.hpp"
#include "circle_collider.hpp"

void golem_component::start() {
	m_player = get_engine().get_entity(2);
	m_sprite = get_component<sprite_render*>(2);
	m_rigid = get_component<rigid_body*>(0);
	m_health = get_component<health*>(6);
	m_director = get_engine().get_entity(5)->get_component<director*>(0);
	
	m_sprite->get_uv_offset().set_x(3);
	m_sprite->get_uv_offset().set_y(4);
	
	get_transform().set_scale(loli::vec3(1.5, 1.5, 1.0));
}

void golem_component::tick() {
	if (m_health->get_health() <= 0) {
		get_parent()->remove();
		return;
	}
	
	loli::vec3 dir = m_player->get_transform().get_pos() - get_transform().get_pos();
	
	if (dir.length() > 30) {
		get_parent()->remove();
		return;
	}
	
	m_rigid->friction();
	m_rigid->accelerate(dir.normalize(), 1, 1);
	
	m_sprite->get_uv_offset().set_x(3 + (get_ticks() % 60 > 30));
	
	if (get_ticks() % 80 == 0) {
		for (int i = -1; i < 2; i++) {
			loli::vec3 d = m_player->get_transform().get_pos() - get_transform().get_pos();
			float dir = atan2(d.get_y(), d.get_x()) + 30 * M_PI / 180 * i;
			
			loli::entity* proj = get_engine().add_entity();
			
			proj->add_component(new rigid_body());
			proj->add_component(new ghost_projectile(dir, 7.0, 50, 8));
			proj->add_component(new sprite_render(loli::vec2(7, 5)));
			proj->add_component(new circle_collider(0.1));
			
			proj->get_component<sprite_render*>(2)->is_rotate(true);
			
			proj->get_transform().translate(get_transform().get_pos());
			proj->get_transform().set_scale(loli::vec3(1.2, 1.2, 1.0));
			proj->start();
		}
	}
}

void golem_component::remove() {
	m_director->remove(get_parent());
	
	loli::entity* e = get_engine().add_entity();
	e->get_transform().translate(get_transform().get_pos());
	e->add_component(new break_particle());
	e->start();
}