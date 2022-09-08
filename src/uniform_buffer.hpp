#pragma once

#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <GL/glew.h>

namespace loli {
	class uniform_buffer {
		private:
			GLuint m_ubo;
		
		public:
			uniform_buffer(unsigned int size, unsigned int id);
			~uniform_buffer();
			
			void sub_data(void* data, unsigned int offset, unsigned int size);
	};
}

#endif