#pragma once

#ifndef NET_ITEM_H
#define NET_ITEM_H

#include "item.hpp"

class net_item : public item {
	private:
		loli::entity* m_cursor;
	
	public:
		void tick();
		void init();
		void equip();
		void unequip();
		
		void on_collide(loli::entity* e);
};

#endif