#include "flare_gun_item.hpp"

#include "input.hpp"
#include "terrain_collider.hpp"
#include "flare_component.hpp"
#include "emitter_particle.hpp"
#include "trail_particle.hpp"

void flare_item::init() {
	set_spr(loli::vec2(5, 4));
}

void flare_gun_item::init() {
	item::init();
	set_spr(loli::vec2(2, 8));
	
	m_cursor = get_engine().get_entity(4);
	
	set_count(3);
}

void flare_gun_item::equip() {
	item::equip();
	
	get_item().m_size = loli::vec2(0.5, 0.5);
	get_item().m_offset = loli::vec2(1.0, 1.0);
	
	get_sprite().get_uv_offset().set_x(get_spr().get_x());
	get_sprite().get_uv_offset().set_y(get_spr().get_y());
}

void flare_gun_item::unequip() {
	get_render().get_light().get_light(1)->set_intensity(0);
}

void flare_gun_item::tick() {
	if (loli::input::get_mouse(0) && get_ticks() > m_next_fire && get_count() > 0) {
		// get_engine().get_sound_engine().play2D("assets/sound/flare.wav");
		float rot = m_cursor->get_transform().get_rot();
		loli::vec3 dir = loli::vec3(1, 0).rotate(rot);
		
		loli::entity* flare = get_engine().add_entity();
		flare->add_component(new rigid_body());
		flare->add_component(new sprite_render());
		flare->add_component(new flare_component(loli::vec3(dir), 4, 60 * 2));
		flare->add_component(new terrain_collider(0.1));
		flare->add_component(new trail_particle(flare->get_component<rigid_body*>(0), 20, 60 * 7, 0.2));
		flare->add_component(new circle_collider(0.2));
		flare->get_component<trail_particle*>(4)->set_color(loli::vec3(1.0, 0.0, 0.0));
		flare->get_transform().translate(get_transform().get_pos());
		flare->get_transform().rotate(rot);
		flare->start();
		
		m_next_fire = get_ticks() + 50;
		set_count(get_count() - 1);
	}
}
