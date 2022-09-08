#include "ghost_component.hpp"

#include "break_particle.hpp"
#include "ghost_projectile.hpp"
#include "circle_collider.hpp"
#include "entity_type.hpp"

void ghost_component::start() {
	m_player = get_engine().get_entity(2);
	m_cursor = get_engine().get_entity(4);
	m_sprite = get_component<sprite_render*>(2);
	m_rigid = get_component<rigid_body*>(0);
	m_health = get_component<health*>(6);
	m_director = get_engine().get_entity(5)->get_component<director*>(0);
	
	m_sprite->get_uv_offset().set_x(2);
	m_sprite->get_uv_offset().set_y(4);
}

void ghost_component::tick() {
	
	float speed = 3;
	
	if (m_health->get_health() <= 0) {
		get_parent()->remove();
		return;
	}
	
	loli::vec3 dir = m_player->get_transform().get_pos() - get_transform().get_pos();
	
	if (dir.length() > 30) {
		get_parent()->remove();
	}
	
	m_rigid->friction();
	
	if (dir.length() > 2.5)
		m_rigid->projected_accelerate(dir.normalize(), speed, speed);
	else
		m_rigid->projected_accelerate(dir.normalize() * -1, speed, speed);
		
	if (get_ticks() % 60 == 0)
		m_rigid->projected_accelerate(dir.normalize(), 15, 15);
	else if (get_ticks() % 5 == 0)
		m_rigid->projected_accelerate(loli::vec3(rand() % 10 - 5, rand() % 10 - 5).normalize(), 7, 7);
	
	if (get_ticks() % 180 < 60) {
		if (get_ticks() % 20 == 0) {
			loli::vec3 d = m_player->get_transform().get_pos() - get_transform().get_pos();
			float dir = atan2(d.get_y(), d.get_x());
			
			loli::entity* proj = get_engine().add_entity();
			
			proj->add_component(new rigid_body());
			proj->add_component(new ghost_projectile(dir, 9.0, 100, 4));
			proj->add_component(new sprite_render(loli::vec2(7, 4)));
			proj->add_component(new circle_collider(0.1));
			
			proj->get_component<sprite_render*>(2)->is_rotate(true);
			
			proj->get_transform().translate(get_transform().get_pos());
			proj->get_transform().set_scale(loli::vec3(0.5, 0.5, 1.0));
			proj->get_transform().rotate(dir - 45.0 * M_PI / 180.0);
			proj->start();
		}
	}
}

void ghost_component::remove() {
	m_director->remove(get_parent());
	
	loli::entity* e = get_engine().add_entity();
	e->get_transform().translate(get_transform().get_pos());
	e->add_component(new break_particle());
	e->start();
}

void ghost_component::damage(int health) {
	
}

void ghost_component::render() {
	
}

void ghost_component::on_collide(loli::entity* e) {
	
}