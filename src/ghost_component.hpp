#pragma once

#ifndef GHOST_COMPONENT_H
#define GHOST_COMPONENT_H

#include "entity.hpp"
#include "sprite_render.hpp"
#include "rigid_body.hpp"
#include "health.hpp"
#include "director.hpp"
#include "emitter_particle.hpp"
#include "light_manager.hpp"

class ghost_component : public loli::entity_component {
	private:
		sprite_render* m_sprite;
		rigid_body* m_rigid;
		health* m_health;
		director* m_director;
		emitter_particle* m_emitter;
		
		loli::light* m_light;
		
		int m_burn_end;
		
		loli::entity* m_cursor;
		loli::entity* m_player;
		
	public:
		ghost_component() { }
		
		void start();
		
		void tick();
		void render();
		
		void remove();
		
		void damage(int health);
		void on_collide(loli::entity* e);
};

#endif