#include "terrain_collider.hpp"

terrain_collider::terrain_collider(float hitbox) {
	m_hitbox = hitbox;
}

void terrain_collider::start() {
	m_rigid = get_component<rigid_body*>(0);
	m_terrain = get_engine().get_entity(0)->get_component<terrain_component*>(1);
}

bool terrain_collider::is_collide(loli::vec3 pos) {
	for (int i = 0; i < 4; i++) {
		int a = i % 2;
		int b = i / 2;
		
		loli::vec3 c = pos + loli::vec3(a, b) * m_hitbox - m_hitbox / 2;
		
		if (m_terrain->get((int) c.get_x(), (int) c.get_y()) & terrain_component::SOLID)
			return true;
	}
	
	return false;
}

void terrain_collider::tick() {
	loli::vec3 vel = m_rigid->get_velocity();
	
	loli::vec3 pos = get_transform().get_pos();
	loli::vec3 newpos = get_transform().get_pos() + vel;
	
	if (is_collide(newpos)) {
		if (is_collide(loli::vec3(newpos.get_x(), pos.get_y())))
			vel.set_x(0);
		if (is_collide(loli::vec3(pos.get_x(), newpos.get_y())))
			vel.set_y(0);
		
		float s = vel.length() * 60;
		
		m_rigid->set_velocity(loli::vec3());
		
		m_rigid->set_velocity(vel);
	}
}