#pragma once

#ifndef PICKAXE_ITEM_H
#define PICKAXE_ITEM_H

#include "item.hpp"
#include "terrain_component.hpp"

class pickaxe_item : public item {
	private:
		loli::entity* m_cursor;
		terrain_component* m_terrain;
	
	public:
		void tick();
		void init();
		void equip();
		void unequip();
		
		void on_collide(loli::entity* e);
};

#endif