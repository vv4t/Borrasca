#pragma once

#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "entity.hpp"
#include "math3d.hpp"

class rigid_body : public loli::entity_component {
	private:
		loli::vec3 m_velocity;
		float m_drag = 10.0;
		
		bool m_grounded = false;
		
	public:
		static float time_step;
	
		void tick();
		
		void friction();
		void add_force(loli::vec3 f);
		
		void accelerate(loli::vec3 dir, float accel, float max_vel);
		void projected_accelerate(loli::vec3 dir, float accel, float max_vel);
		
		void set_velocity(loli::vec3 v);
		loli::vec3 get_velocity();
		
		void set_drag(float f);
		float get_drag();
		
		void is_grounded(bool b);
};

#endif