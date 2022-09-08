#include "torch_item.hpp"

#include "entity_type.hpp"
#include "health.hpp"

void torch_item::init() {
	item::init();
	set_spr(loli::vec2(1, 8));
	
	m_cursor = get_engine().get_entity(4);
}

void torch_item::equip() {
	item::equip();
	
	get_item().m_size = loli::vec2(1, 1);
	get_item().m_offset = loli::vec2(1, 2);
	
	get_sprite().get_uv_offset().set_x(get_spr().get_x());
	get_sprite().get_uv_offset().set_y(get_spr().get_y());
	
	get_render().get_light().get_light(1)->set_col(loli::vec3(1.0, 0.8, 0.6));
	get_parent()->add_component(new emitter_particle())->start();
	get_component<emitter_particle*>(3)->set_color(loli::vec3(1.0, 0.0, 0.0));
	
	m_cursor->get_component<circle_collider*>(2)->set_radius(2.0);
}

void torch_item::unequip() {
	get_render().get_light().get_light(1)->set_intensity(0);
	get_parent()->remove_component(3);
	m_cursor->get_component<circle_collider*>(2)->set_radius(0.25);
}

void torch_item::tick() {
	if (get_ticks() % 60 == 0) {
		// get_engine().get_sound_engine().play2D("assets/sound/fire.wav");
	}
	
	get_render().get_light().get_light(1)->set_pos(loli::vec3(get_transform().get_pos()).set_z(1.0));
	get_render().get_light().get_light(1)->set_intensity(cos(get_ticks() / 2.0f) * 0.25 + 3.0f);
}

void torch_item::on_collide(loli::entity* e) {
	if (get_ticks() % 30 == 0) {
		if (e->get_type() == ENTITY_GHOST) {
			e->get_component<health*>(6)->remove_hp(8);
		}
		
		if (e->get_type() == ENTITY_BOSS) {
			e->get_component<health*>(4)->remove_hp(8);
		}
	}
}
