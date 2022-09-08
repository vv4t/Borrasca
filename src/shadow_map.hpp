#pragma once

#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include "entity.hpp"
#include "frame_buffer.hpp"
#include "terrain_component.hpp"
#include "mesh.hpp"
#include "math3d.hpp"

class shadow_map : public loli::entity_component {
	private:
		typedef std::pair<float, loli::vec2> ray;
		
		loli::frame_buffer* m_fbo;
		
		loli::mesh* m_shadow_mesh;
		terrain_component* m_terrain;
		
		int m_shadow_size;
		
		loli::vec2 raycast(loli::vec2 start, float dir, int rage);
	
	public:
		shadow_map() { }
		
		void map(loli::vec2 pos, int radius);
		
		void start();
		void tick();
		void render();
};

#endif