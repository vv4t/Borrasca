#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "transform.hpp"
#include "math3d.hpp"

namespace loli {
	class camera {
		private:
			mat4 m_projection;
			transform m_transform;
		
		public:
			camera();
			
			void set_projection(mat4 m);
			mat4 to_projected_view(mat4 m);
			
			transform& get_transform();
			mat4& get_proj();
	};
}

#endif