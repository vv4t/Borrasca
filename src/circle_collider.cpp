#include "circle_collider.hpp"

#include <algorithm>

void collision_engine::add_collider(circle_collider* collider) {
	m_colliders.push_back(collider);
}

void collision_engine::remove_collider(circle_collider* collider) {
	m_colliders.erase(
		std::remove(m_colliders.begin(), m_colliders.end(), collider),
		m_colliders.end()
	);
}

circle_collider* collision_engine::get(int id) {
	return m_colliders[id];
}

int collision_engine::size() {
	return m_colliders.size();
}

void collision_engine::clear() {
	m_colliders.clear();
}



circle_collider::circle_collider(float radius) {
	m_radius = radius;
}

float circle_collider::get_radius() {
	return m_radius;
}

void circle_collider::start() {
	m_rigid = get_component<rigid_body*>(0);
	
	m_collision = get_engine().get_entity(1)->get_component<collision_engine*>(0);
	m_collision->add_collider(this);
}

void circle_collider::tick() {
	if (abs(get_transform().get_pos().get_x() - get_cam().get_transform().get_pos().get_x()) > 5
		|| abs(get_transform().get_pos().get_y() - get_cam().get_transform().get_pos().get_y()) > 5)
		return;
	
	for (int i = 0; i < m_collision->size(); i++) {
		circle_collider* c = m_collision->get(i);
		
		if (c == this) continue;
		
		loli::entity* parent = c->get_parent();
		
		rigid_body* rb = parent->get_component<rigid_body*>(0);
		
		loli::vec3 p1 = get_transform().get_pos() + m_rigid->get_velocity();
		loli::vec3 p2 = parent->get_transform().get_pos() + rb->get_velocity();
		
		float d = (p1 - p2).length();
		float r = get_radius() + c->get_radius();
		
		if (r > d)
			get_parent()->on_collide(parent);
	}
}

void circle_collider::remove() {
	m_collision->remove_collider(this); 
}

void circle_collider::set_radius(float f) {
	m_radius = f;
}