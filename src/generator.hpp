#pragma once

#ifndef GENERATOR_H
#define GENERATOR_H

#include "sprite_render.hpp"

class generator : public loli::entity_component {
	private:
		sprite_render* m_sprite;
		bool m_on;
	
	public:
		static int on;
		
		void start();
		void tick();
		
		void on_collide(loli::entity* e);
		
		void turn_on();
		bool is_on();
};

#endif