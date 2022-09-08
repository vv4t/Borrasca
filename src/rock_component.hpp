#pragma once

#ifndef ROCK_COMPONENT_H
#define ROCK_COMPONENT_H

#include "entity.hpp"
#include "rigid_body.hpp"

class rock_component : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		
	public:
		rock_component() { }
		
		void start();
		void tick();
		void remove();
		
		void on_collide(loli::entity* e);
};

#endif