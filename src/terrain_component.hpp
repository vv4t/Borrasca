#pragma once

#ifndef TERRAIN_COMPONENT_H
#define TERRAIN_COMPONENT_H

#include "bitmap.hpp"
#include "entity.hpp"
#include "math3d.hpp"
#include "mesh.hpp"
#include "circle_collider.hpp"
#include "rigid_body.hpp"

class shadow_map;

class terrain_component : public loli::entity_component {
	private:
		int map_w;
		int map_h;
		
		int map_chunk_w;
		int map_chunk_h;
		
		int chunk_w = 16;
		int chunk_h = 16;
		
		int m_active_chunks[4];
		int* m_chunk_ptr;
		
		loli::mesh* m_mesh;
		std::vector<loli::vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		
		unsigned char* m_map;
		
		void add_block(loli::vec3 pos, loli::vec2 tex);
		
		void add_wall(loli::vec3 p0, loli::vec3 p1, loli::vec2 tex, int shift);
		void add_wall(loli::vec3 pos, loli::vec3 normal, loli::vec2 tex);
		void add_wall(loli::vec3 pos, loli::vec2 tex, int shift);
		
		void add_tile(loli::vec3 pos, loli::vec2 tex, int shift);
		
		void init();
		void clean();
		
	public:
		enum {
			SOLID  = 0b00000001,
			OPAQUE = 0b00000010,
			LIQUID = 0b00000100,
		};
	
		terrain_component() {}
		~terrain_component();
		
		void tick();
		void render();
		
		void load_map(loli::bitmap* bmp);
		void load_mesh();
		
		int get_width();
		int get_height();
		
		unsigned char get(int x, int y);
};

#endif
