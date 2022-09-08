#pragma once

#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "entity.hpp"
#include "rigid_body.hpp"

#include <vector>

class circle_collider;

class collision_engine : public loli::entity_component {
	private:
		std::vector<circle_collider*> m_colliders;
	
	public:
		void add_collider(circle_collider* collider);
		void remove_collider(circle_collider* collider);
		circle_collider* get(int id);
		
		void clear();
		
		int size();
};

class circle_collider : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		collision_engine* m_collision;
	
		float m_radius;
	
	public:
		circle_collider(float radius);
		
		float get_radius();
		void set_radius(float radius);
		
		void start();
		void tick();
		
		void remove();
};

#endif