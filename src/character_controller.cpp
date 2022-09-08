#include "character_controller.hpp"

#include "input.hpp"
#include "entity_type.hpp"

void character_controller::start() {
	m_speed = 0.1f;
	m_flashlight_dir = 0.0f;
	m_rigid = get_component<rigid_body*>(0);
	m_sprite = get_component<sprite_render*>(2);
	m_terrain = get_engine().get_entity(0)->get_component<terrain_component*>(1);
}

loli::vec3 character_controller::get_axis() {
	bool forward = loli::input::get_key(loli::input::KEY_W);
	bool left = loli::input::get_key(loli::input::KEY_A);
	bool back = loli::input::get_key(loli::input::KEY_S);
	bool right = loli::input::get_key(loli::input::KEY_D);
	
	loli::vec3 axis;
	axis.set_x(right + left * -1);
	axis.set_y(forward + back * -1);
	
	return axis;
}

loli::vec2 character_controller::get_mouse() {
	float dx = loli::input::get_mouse_x();
	float dy = loli::input::get_mouse_y();
	
	return loli::vec2(dx, dy);
}

void character_controller::is_water() {
	if (m_terrain->get((int) get_transform().get_pos().get_x(), (int) get_transform().get_pos().get_y()) & terrain_component::LIQUID) {
		m_speed = 3;
		get_transform().set_scale(loli::vec3(1, 0.7, 1));
		m_sprite->get_uv_size().set_y(0.7);
	} else {
		m_speed = 5;
		get_transform().set_scale(loli::vec3(1, 1, 1));
		m_sprite->get_uv_size().set_y(1);
	}
}

void character_controller::move(loli::vec3 axis) {
	loli::vec3 velocity = axis.rotate(get_cam().get_transform().get_rot()) * m_speed;
	
	m_rigid->friction();
	
	if (velocity.length() > 0)
		m_rigid->accelerate(velocity.normalize(), m_speed, m_speed);
}

void character_controller::animate(loli::vec2 mouse, loli::vec3 axis) {
	float dx = mouse.get_x();
	float dy = mouse.get_y();
	
	if (abs(dy) > abs(dx) && dy > 0) m_state = 1;
	if (abs(dx) > abs(dy) && dx < 0) m_state = 3;
	if (abs(dy) > abs(dx) && dy < 0) m_state = 0;
	if (abs(dx) > abs(dy) && dx > 0) m_state = 2;
	
	if (axis.length() > 0) {
		/*if (m_speed == 3) {
			if (get_ticks() % 60 == 0) {
				get_engine().get_sound_engine().play2D("assets/sound/water.wav");
			}
		} else if (m_speed == 5) {
			if (get_ticks() % 60 == 0) {
				get_engine().get_sound_engine().play2D("assets/sound/gravel.wav");
			}
		}*/
		
		m_frame = 1 + (get_ticks() % 30 > 15);
	} else
		m_frame = 0;
	
	m_sprite->get_uv_offset().set_x(m_frame);
	m_sprite->get_uv_offset().set_y(m_state);
}

void character_controller::cam_rot() {
	bool left = loli::input::get_key(loli::input::KEY_Q);
	bool right = loli::input::get_key(loli::input::KEY_E);
	
	float a = (left + right * -1) * 0.05f;
	
	get_cam().get_transform().rotate(a);
}

void character_controller::tick() {
	loli::vec3 input = get_axis();
	loli::vec2 mouse = get_mouse();
	
	is_water();
	move(input);
	animate(mouse, input);
	
	cam_rot();
	
	get_cam().get_transform().set_pos(get_transform().get_pos());
}

void character_controller::on_collide(loli::entity* entity) {
	
}

void character_controller::freeze() {
	m_freeze = true;
	
	m_rigid->set_velocity(loli::vec3());
	
	m_frame = 0;
	m_state = 2;
	
	m_sprite->get_uv_offset().set_x(m_frame);
	m_sprite->get_uv_offset().set_y(m_state);
}
