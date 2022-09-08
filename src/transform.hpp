#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math3d.hpp"

namespace loli {
	class transform {
		private:
			float m_rot;
			loli::vec3 m_pos;
			loli::vec3 m_scale;
			
			loli::mat4 m_transform;
			
			bool m_update;
			void mat_update();
		
		public:
			transform();
			
			void rotate(float v);
			void translate(loli::vec3 v);
			void scale(loli::vec3 v);
			
			void set_rot(float v);
			void set_pos(loli::vec3 v);
			void set_scale(loli::vec3 v);
			
			vec3 get_pos();
			vec3 get_scale();
			float get_rot();
			
			mat4 get_mat();
	};
};

#endif