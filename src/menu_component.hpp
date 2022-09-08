#pragma once

#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "entity.hpp"
#include "game.hpp"

class menu_component : public loli::entity_component {
	private:
		game* g;
	
	public:
		menu_component(game* a);
		void tick();
		void on_gui();
};

#endif