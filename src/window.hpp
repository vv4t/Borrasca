#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GLFW/glfw3.h>

namespace loli {
	class window {
		private:
			GLFWwindow* m_window;
			
			int m_width;
			int m_height;
		
		public:
			window(int width, int height, const char* title);
			
			void set_cursor_pos(float x, float y);
			void close();
			void swap_buffer();
			
			float get_time();
			
			int get_width();
			int get_height();
			
			bool loop();
			
			GLFWwindow* get_window();
	};
};

#endif