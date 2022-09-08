#pragma once

#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "entity.hpp"
#include "rigid_body.hpp"
#include "sprite_render.hpp"
#include "terrain_component.hpp"

class character_controller : public loli::entity_component {
	private:
		float m_speed;
		rigid_body* m_rigid;
		sprite_render* m_sprite;
		terrain_component* m_terrain;
		
		float m_flashlight_dir;
		
		loli::vec3 get_axis();
		loli::vec2 get_mouse();
		
		void is_water();
		void animate(loli::vec2 mouse, loli::vec3 axis);
		void move(loli::vec3 axis);
		void cam_rot();
		
		bool m_freeze = false;
	
	public:
		int m_state;
		int m_frame;
		
		character_controller() { }
		
		void start();
		void tick();
		void on_collide(loli::entity* entity);
		
		void freeze();
};

#endif
