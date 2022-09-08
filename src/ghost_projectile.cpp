#include "ghost_projectile.hpp"

#include "entity_type.hpp"
#include "health.hpp"

ghost_projectile::ghost_projectile(float dir, float speed, int life, int damage) {
	m_dir = dir;
	m_speed = speed;
	m_life = life;
	m_damage = damage;
}

void ghost_projectile::start() {
	m_rigid = get_component<rigid_body*>(0);
	m_end = get_ticks() + m_life;
	
	loli::vec3 vel = loli::vec3(cos(m_dir), sin(m_dir));
	m_rigid->projected_accelerate(vel, m_speed, m_speed);
	m_terrain = get_engine().get_entity(0)->get_component<terrain_component*>(1);
}

void ghost_projectile::tick() {
	if (m_terrain->get((int) get_transform().get_pos().get_x(), (int) get_transform().get_pos().get_y()) & terrain_component::SOLID) {
		get_parent()->remove();
		return;
	}
	
	if (get_ticks() > m_end) {
		get_parent()->remove();
		return;
	}
}

void ghost_projectile::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_PLAYER) {
		e->get_component<health*>(5)->remove_hp(m_damage);
		
		get_parent()->remove();
	}
}