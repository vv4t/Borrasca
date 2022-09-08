#pragma once

#ifndef TORCH_H
#define TORCH_H

#include "item.hpp"
#include "emitter_particle.hpp"

class torch_item : public item {
	private:
		loli::entity* m_cursor;
	
	public:
		void init();
		void tick();
		void equip();
		void unequip();
		
		void on_collide(loli::entity* e);
};

#endif