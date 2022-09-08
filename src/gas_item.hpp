#pragma once

#ifndef GAS_ITEM_H
#define GAS_ITEM_H

#include "item.hpp"

class gas_item : public item {
	private:
		loli::entity* m_cursor;
	
	public:
		void init();
		void equip();
		void unequip();
		void on_collide(loli::entity* e);
};

#endif