#pragma once

#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "entity.hpp"
#include "object_pool.hpp"

class particle_system : public loli::entity_component {
	
	protected:
		class particle {
			public:
				loli::vec3 m_start_pos;
				loli::vec3 m_pos;
				loli::vec3 m_vel;
				
				int m_end;
		};
		
		virtual void p_init(particle* p) { }
		virtual void p_move(particle* p) { }
		
	private:
		loli::object_pool<particle> m_particles;
		loli::mesh* m_mesh;
		
		loli::vec3 m_color = loli::vec3(1, 1, 1);
		
		int m_count;
	
	public:
		particle_system(int count);
		
		void start();
		
		void tick();
		void render();
		
		void remove();
		
		void set_color(loli::vec3 col);
};

#endif