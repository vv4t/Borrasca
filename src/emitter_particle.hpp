#pragma once

#ifndef EMITTER_PARTICLE_H
#define EMITTER_PARTICLE_H

#include "particle_system.hpp"

class emitter_particle : public particle_system {
	private:
		void p_init(particle* p);
		void p_move(particle* p);
		
		float m_speed;
		int m_life;
		
		bool m_hide = false;
	
	public:
		emitter_particle(float speed = 0.1, int life = 10);
		
		void tick();
		void render();
		
		void hide(bool b);
};

#endif