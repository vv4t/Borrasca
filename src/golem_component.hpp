#pragma once

#ifndef GOLEM_H
#define GOLEM_H

#include "entity.hpp"
#include "rigid_body.hpp"
#include "sprite_render.hpp"
#include "director.hpp"
#include "health.hpp"

class golem_component : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		sprite_render* m_sprite;
		director* m_director;
		health* m_health;
		loli::entity* m_player;
	
	public:
		golem_component() {}
		
		void start();
		void tick();
		
		void remove();
};

#endif