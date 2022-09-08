#pragma once

#ifndef FLARE_COMPONENT_H
#define FLARE_COMPONENT_H

#include "entity.hpp"
#include "rigid_body.hpp"
#include "sprite_render.hpp"

class flare_component : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		sprite_render* m_sprite;
		loli::light* m_light;
		
		bool m_landed = false;
		
		loli::vec3 m_dir;
		float m_speed;
		int m_life;
		int m_start;
		int m_end;
		
	public:
		flare_component(loli::vec3 dir, float speed, int life);
		
		void start();
		void tick();
		void remove();
		
		void on_collide(loli::entity* e);
};

#endif