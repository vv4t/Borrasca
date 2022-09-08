#pragma once

#ifndef FLASHLIGHT_COMPONENT_H
#define FLASHLIGHT_COMPONENT_H

#include "entity.hpp"
#include "director.hpp"

class flashlight_component : public loli::entity_component {
	private:
		director* m_director;
		loli::entity* m_player;
		
		float m_radius = 0;
		float m_dir = 0;
		
	public:
		flashlight_component() {}
		
		void start();
		void tick();
		void on_collide(loli::entity* e);
		
		void on_gui();
		
		void add_power(float f);
};

#endif