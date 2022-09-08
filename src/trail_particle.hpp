#pragma once

#ifndef TRAIL_PARTICLE_H
#define TRAIL_PARTICLE_H

#include "particle_system.hpp"
#include "rigid_body.hpp"

class trail_particle : public particle_system {
	private:
		int m_reset;
		float m_speed;
		
		void p_init(particle* p);
		void p_move(particle* p);
		
		rigid_body* m_rigid;
	
	public:
		trail_particle(rigid_body* rigid, int count, int reset, float speed);
};

#endif