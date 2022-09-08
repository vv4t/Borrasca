#pragma once

#define VERTEX_SIZE 32

#ifndef VERTEX_H
#define VERTEX_H

#include "math3d.hpp"

namespace loli {
	class vertex {
		private:
			loli::vec3 m_pos;
			loli::vec3 m_normal;
			loli::vec2 m_tex;
		
		public:
			vertex() { }
			
			vertex(vec3 pos, vec3 normal, vec2 tex) {
				m_pos = pos;
				m_normal = normal;
				m_tex = tex;
			}
			
			vec3 get_pos() { return m_pos; }
			vec3 get_normal() { return m_normal; }
			vec2 get_tex() { return m_tex; }
	};
}

#endif