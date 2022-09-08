#pragma once

#ifndef BREAK_PARTICLE_H
#define BREAK_PARTICLE_H

#include "particle_system.hpp"

class break_particle : public particle_system {
	private:
		void p_init(particle* p);
		void p_move(particle* p);
		
		int m_end;
	
	public:
		break_particle() : particle_system(10) {}
		
		void start();
		void tick();
};

#endif