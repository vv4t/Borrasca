#pragma once

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "vertex.hpp"

namespace loli {
	class mesh {
		private:
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ebo;
			
			int m_vertex_size;
			int m_element_size;
			
			char* to_buffer(vertex* data, int size);
		
		public:
			mesh();
			~mesh();
			
			mesh& init(vertex* vertices, int size);
			mesh& init_buffer(int size);
			
			mesh& index(unsigned int* indices, int size);
			
			void bind();
			void unbind();
			
			void sub_vertices(vertex* vertices, unsigned int offset, unsigned int size);
			void sub_indices(unsigned int* indices, unsigned int offset, unsigned int size);
			
			int vertex_size();
			int element_size();
	};
}

#endif