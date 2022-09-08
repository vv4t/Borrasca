#pragma once

#ifndef BAT_COMPONENT_H

#include "entity.hpp"
#include "sprite_render.hpp"
#include "rigid_body.hpp"
#include "director.hpp"

class bat_component : public loli::entity_component {
	private:
		loli::entity* m_player;
		sprite_render* m_sprite;
		rigid_body* m_rigid;
		director* m_director;
		
		loli::vec3 m_bat_pos;
		
		float m_dir = 0.0f;
		
		void accelerate(loli::vec3 dir, float accel, float max_vel);
	
	public:
		bat_component() { }
		
		void start();
		void tick();
		
		void remove();
		void on_collide(loli::entity* e);
};

#endif