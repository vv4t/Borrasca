#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "bitmap.hpp"

#include <GL/glew.h>

namespace loli {
	class texture {
		private:
			GLuint m_tex;
			
			int m_width;
			int m_height;
		
		public:
			texture(unsigned char* data, unsigned int width, unsigned int height);
			texture(bitmap* bmp);
			~texture();
			
			void bind(int sampler);
	};
}

#endif