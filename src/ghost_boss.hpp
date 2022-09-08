#pragma once

#ifndef GHOST_BOSS_H
#define GHOST_BOSS_H

#include "entity.hpp"
#include "sprite_render.hpp"
#include "rigid_body.hpp"
#include "director.hpp"
#include "health.hpp"

class ghost_boss : public loli::entity_component {
	private:
		sprite_render* m_sprite;
		rigid_body* m_rigid;
		director* m_director;
		health* m_health;
		
		loli::entity* m_player;
		
		void shoot_spike(float dir);
		void shoot_orb(float dir);
	
	public:
		void start();
		void tick();
		
		void remove();
};

#endif