#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "render_engine.hpp"
#include "entity.hpp"
#include "window.hpp"

// #include <irrklang/irrKlang.h>

namespace loli {
	class entity;
	class core_engine;
	class core_engine {
		private:
			window* m_win;
			render_engine* m_render_engine;
			// irrklang::ISoundEngine* m_sound_engine;
			
			object_pool<entity> m_entity_pool;
			
			unsigned int m_ticks = 0;
			bool m_start = false;
			
			void tick();
			void render();
		
		public:
			core_engine(window* win);
			~core_engine();
			
			void start();
			void run();
			
			bool started();
			
			entity* add_entity();
			entity* get_entity(unsigned int id);
			
			void remove_entity(entity* e);
			
			loli::render_engine& get_render_engine();
			// irrklang::ISoundEngine& get_sound_engine();
			
			unsigned int get_ticks();
	};
}

#endif
