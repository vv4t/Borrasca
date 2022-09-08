#pragma once

#ifndef FLAMABLE_H
#define FLAMABLE_H

#include "entity.hpp"
#include "emitter_particle.hpp"
#include "light_manager.hpp"

class flamable : public loli::entity_component {
	private:
		emitter_particle* m_emitter;
		loli::light* m_light;
		
		int m_burn_end;
		
	public:
		void start();
		void tick();
		void on_collide(loli::entity* e);
		void remove();
};

#endif