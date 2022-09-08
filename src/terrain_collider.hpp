#pragma once

#ifndef TERRAIN_COLLIDER_H
#define TERRAIN_COLLIDER_H

#include "entity.hpp"
#include "rigid_body.hpp"
#include "terrain_component.hpp"

class terrain_collider : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		terrain_component* m_terrain;
		
		bool is_collide(loli::vec3 pos);
		float m_hitbox;
		
	public:
		terrain_collider(float hitbox = 0.8);
		
		void start();
		void tick();
};

#endif