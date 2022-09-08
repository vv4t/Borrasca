#pragma once

#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "object_pool.hpp"
#include "render_engine.hpp"
#include "uniform_buffer.hpp"
#include "math3d.hpp"

namespace loli {
	class light {
		private:
			vec3 m_pos;
			float m_intensity;
			
			vec3 m_col;
			float m_dir;
			
			float m_angle;
			int m_shadow;
			float padding[2];
		
		public:
			light(vec3 pos, vec3 col, float intensity, float dir, float angle);
			
			void set_pos(vec3 v);
			void set_col(vec3 v);
			void set_intensity(float f);
			void set_dir(float f);
			void set_angle(float f);
			void enable_shadow(bool b);
			
			vec3 get_pos();
			vec3 get_col();
			
			float get_dir();
			float get_angle();
			float get_intensity();
			
			bool is_shadow();
	};
	
	class render_engine;
	
	class light_manager {
		private:
			render_engine* m_render;
			
			uniform_buffer* m_ubo;
			
			object_pool<light> m_light_pool;
			char* m_block;
			
			int m_light_size;
			int m_light_count;
			
		public:
			light_manager(render_engine* render, int size);
			
			light* add_light(vec3 position, vec3 col, float intensity, float dir, float angle);
			light* get_light(int id);
			
			void update_lights();
			void update_light(int id);
			
			void remove_light(light* _light);
	};
}

#endif