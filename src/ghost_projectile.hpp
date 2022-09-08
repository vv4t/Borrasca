#pragma once

#ifndef GHOST_PROJECTILE_H
#define GHOST_PROJECTILE_H

#include "entity.hpp"
#include "rigid_body.hpp"
#include "terrain_component.hpp"

class ghost_projectile : public loli::entity_component {
	private:
		terrain_component* m_terrain;
	
		float m_dir;
		float m_speed;
		
		int m_life;
		int m_end;
		int m_damage;
		
		rigid_body* m_rigid;
	
	public:
		ghost_projectile(float dir, float speed, int life, int damage);
		
		void start();
		void tick();
		
		void on_collide(loli::entity* e);
};

#endif