#pragma once

#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "light_manager.hpp"
#include "uniform_buffer.hpp"
#include "object_pool.hpp"
#include "frame_buffer.hpp"

typedef GLuint uniform_location;

namespace loli {
	class light_manager;
	
	class render_engine {
		private:
			object_pool<mesh> m_mesh_pool;
			object_pool<shader> m_shader_pool;
			object_pool<texture> m_texture_pool;
			object_pool<uniform_buffer> m_ubo_pool;
			object_pool<frame_buffer> m_fbo_pool;
			
			light_manager* m_lights;
			
			mesh* m_mesh_id;
			shader* m_shader_id;
			
			camera m_cam;
			
			void update_light();
		
		public:
			enum {
				triangle = GL_TRIANGLES,
				triangle_fan = GL_TRIANGLE_FAN
			};
		
			render_engine();
			~render_engine();
			
			void viewport(int x, int y, int w, int h);
			void clear_color(float r, float g, float b, float a);
			void clear();
			
			mesh* add_mesh();
			shader* add_shader(char* vs, char* fs);
			texture* add_texture(bitmap* bmp);
			uniform_buffer* add_ubo(unsigned int size, unsigned int id);
			frame_buffer* add_fbo(unsigned int width, unsigned int height);
			
			void remove_mesh(mesh* _mesh);
			
			void bind_mesh(int id);
			void bind_shader(int id);
			void bind_texture(int id, int sampler);
			
			void bind_mesh(mesh* _mesh);
			void bind_shader(shader* _shader);
			void bind_texture(texture* _texture, int sampler);
			
			mesh* get_mesh(unsigned int id);
			shader* get_shader(unsigned int id);
			texture* get_texture(unsigned int id);
			
			camera& get_cam();
			light_manager& get_light();
			mesh* get_mesh();
			shader* get_shader();
			
			void draw_arrays(GLenum mode, int start, int size);
			void draw_elements(int start, int size);
			
			void gui_img(int sample, loli::vec2 pos, loli::vec2 size, loli::vec2 uv_pos, loli::vec2 uv_size);
	};
}

#endif