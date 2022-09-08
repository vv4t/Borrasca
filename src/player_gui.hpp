#pragma once

#ifndef PLAYER_GUI_H
#define PLAYER_GUI_H

#include "entity.hpp"
#include "health.hpp"

class player_gui : public loli::entity_component {
	private:
		health* m_health;
		int m_start_dead;
	
	public:
		void start();
		void tick();
		void on_gui();
};

#endif