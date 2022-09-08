#pragma once

#ifndef ASSETLIB_H
#define ASSETLIB_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

#include "vertex.hpp"
#include "bitmap.hpp"

namespace loli {
	class assetlib {
		private:
			std::map<std::string, char*>		m_files;
			std::map<std::string, bitmap*>		m_bitmaps;
		
		public:
			assetlib() { }
			
			char* 		load_file(char* path);
			bitmap*		load_bitmap(char* path);
			
			void get_bitmap(int i);
	};
}

#endif