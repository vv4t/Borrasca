#pragma once

#ifndef PUSHABLE_H
#define PUSHABLE_H

#include "entity.hpp"
#include "rigid_body.hpp"

class pushable : public loli::entity_component {
	private:
		rigid_body* m_rigid;
	
	public:
		void start();
		void tick();
		
		void on_collide(loli::entity* e);
};

#endif