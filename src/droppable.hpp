#pragma once

#ifndef DROPPABLE_H
#define DROPPABLE_H

#include "entity.hpp"
#include "sprite_render.hpp"
#include "rigid_body.hpp"

class droppable : public loli::entity_component {
	private:
		int m_type;
		
		sprite_render* m_sprite;
		rigid_body* m_rigid;
	
	public:
		droppable(int type);
	
		void start();
		void tick();
		
		void on_collide(loli::entity* e);
};

#endif