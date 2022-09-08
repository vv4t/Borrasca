#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "math3d.hpp"
#include <GL/glew.h>

namespace loli {
	class shader {
		private:
			GLuint m_program;
			
			int m_uniform_count;
			
			char** m_uniform_names;
			GLuint* m_uniform_locations;
			
			GLuint get_uniform_location(char* name);
		
		public:
			shader() { }
			shader(char* vs_src, char* fs_src);
			
			void load_uniforms();
			
			void uniform_int(char* uniform_name, int i);
			void uniform_float(char* uniform_name, float f);
			void uniform_vec2(char* uniform_name, vec2 v);
			void uniform_vec3(char* uniform_name, vec3 v);
			void uniform_mat4(char* uniform_name, mat4 m);
			void uniform_block(char* uniform_name, unsigned int id);
			
			void bind();
			void dispose();
	};
}

#endif