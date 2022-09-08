#pragma once

#ifndef GAME_H
#define GAME_H

#include "core_engine.hpp"
#include "render_engine.hpp"
#include "assetlib.hpp"
#include "window.hpp"

class game {
	private:
		loli::window* win;
		loli::assetlib assetlib;
		loli::core_engine* engine;
		loli::render_engine* render;
	
	public:
		game();
		~game();
		
		void init();
		void init_menu();
		void init_game();
		void clean();
};

#endif