#pragma once

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <GL/glew.h>

namespace loli {
	class frame_buffer {
		private:
			GLuint m_fbo;
			GLuint m_frame;
			
			int m_width;
			int m_height;
			
		public:
			frame_buffer(int width, int height);
			~frame_buffer();
			
			void bind();
			void unbind();
			
			void bind_frame(int sampler);
			
			int get_width();
			int get_height();
	};
}

#endif