#pragma once

#ifndef BITMAP_H
#define BITMAP_H

namespace loli {
	class bitmap {
		private:
			unsigned char* m_data;
			
			unsigned int m_width;
			unsigned int m_height;
		
		public:
			bitmap(unsigned char* data, unsigned int width, unsigned int height);
			~bitmap();
			
			unsigned int get_width();
			unsigned int get_height();
			
			unsigned char get(unsigned int i);
			unsigned char& operator[](unsigned int i);
	};
};

#endif