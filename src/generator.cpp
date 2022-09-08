#include "generator.hpp"

#include "entity_type.hpp"
#include "rigid_body.hpp"

int generator::on = 0;

void generator::start() {
	m_sprite = get_component<sprite_render*>(2);
	
	m_sprite->get_uv_offset().set_x(6);
	m_sprite->get_uv_offset().set_y(0);
	
	m_sprite->get_uv_size().set_x(2);
	m_sprite->get_uv_size().set_y(2);
}

void generator::tick() {
	
}

void generator::on_collide(loli::entity* e) {
	rigid_body* rb = e->get_component<rigid_body*>(0);
	rb->set_velocity(loli::vec3());
}

void generator::turn_on() {
	loli::vec3 dir =  loli::vec3(29, 69) - get_transform().get_pos();
	float a = atan2(dir.get_y(), dir.get_x());
	
	get_render().get_light().add_light(get_transform().get_pos(), loli::vec3(1.0, 1.0, 0.7), 14.0, a, 0.5);
	m_on = true;
	
	generator::on++;
}

bool generator::is_on() {
	return m_on;
}