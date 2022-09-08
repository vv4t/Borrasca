#include "net_item.hpp"

#include "input.hpp"
#include "entity_type.hpp"

void net_item::init() {
	item::init();
	set_spr(loli::vec2(0, 8));
	
	m_cursor = get_engine().get_entity(4);
}

void net_item::equip() {
	item::equip();
	
	get_item().m_size = loli::vec2(1, 1);
	get_item().m_offset = loli::vec2(0, 0);
	
	get_sprite().get_uv_offset().set_x(get_spr().get_x());
	get_sprite().get_uv_offset().set_y(get_spr().get_y());
}

void net_item::unequip() {

}

void net_item::tick() {
	if (loli::input::get_mouse(0)) {
		int state = get_char().m_state;
		
		float rot = m_cursor->get_transform().get_rot();
		
		if (state == 0 || state == 2) {
			get_item().m_size.set_x(1);
			get_item().m_offset = loli::vec2(-4, 0) + loli::vec2(6, 6).rotate(rot - get_cam().get_transform().get_rot() - 0.78);
		} else {
			get_item().m_size.set_x(-1);
			get_item().m_offset = loli::vec2(-4, 0) + loli::vec2(-6, 6).rotate(-rot + get_cam().get_transform().get_rot() + 0.78);
		}
		
		get_transform().set_rot(rot - 0.78);
	} else {
		get_item().m_size.set_x(1);
		get_item().m_offset = loli::vec2(3, 4);
	}
}

void net_item::on_collide(loli::entity* e) {
	if (loli::input::get_mouse(0)) {
		if (e->get_type() == ENTITY_BAT) {
			e->remove();
		}
	}
}