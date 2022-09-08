#pragma once

#ifndef FLARE_GUN_ITEM_H
#define FLARE_GUN_ITEM_H

#include "item.hpp"

class flare_item : public item {
	private:
	
	public:
		void init();
};

class flare_gun_item : public item {
	private:
		loli::entity* m_cursor;
		int m_next_fire;
		
	public:
		void init();
		void tick();
		void equip();
		void unequip();
};

#endif