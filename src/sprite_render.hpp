#pragma once

#ifndef SPRITE_RENDER_H
#define SPRITE_RENDER_H

#include "entity.hpp"
#include "math3d.hpp"

class sprite_render : public loli::entity_component {
	private:
		loli::vec2 m_uv_offset;
		loli::vec2 m_uv_size;
		
		bool m_rot;
		
		loli::vec4 m_color;
	
	public:
		sprite_render();
		sprite_render(loli::vec2 offset);
		
		void tick();
		void render();
		
		loli::vec2& get_uv_size();
		loli::vec2& get_uv_offset();
		
		void set_color(loli::vec4 v);
		
		void is_rotate(bool rotate);
};

#endif
