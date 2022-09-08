#include "pushable.hpp"

#include "entity_type.hpp"

void pushable::start() {
	m_rigid = get_component<rigid_body*>(0);
}

void pushable::tick() {
	m_rigid->friction();
}

void pushable::on_collide(loli::entity* e) {
	if (e->get_type() != ENTITY_PLAYER && e->get_type() != ENTITY_BARREL) return;
	
	rigid_body* rb = e->get_component<rigid_body*>(0);
	
	loli::vec3 d = get_transform().get_pos() - e->get_transform().get_pos();
	float s = d.length() * 2;
	
	m_rigid->set_velocity(loli::vec3());
	m_rigid->accelerate(d.normalize(), s, s);
	
	rb->set_velocity(loli::vec3());
}