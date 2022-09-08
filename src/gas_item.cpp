#include "gas_item.hpp"

#include "entity_type.hpp"
#include "circle_collider.hpp"
#include "generator.hpp"

void gas_item::init() {
	item::init();
	set_spr(loli::vec2(8, 8));
	
	m_cursor = get_engine().get_entity(4);
}

void gas_item::equip() {
	m_cursor->get_component<circle_collider*>(2)->set_radius(0.25);
	get_sprite().get_uv_offset().set_x(get_spr().get_x());
	get_sprite().get_uv_offset().set_y(get_spr().get_y());
}

void gas_item::unequip() {
	m_cursor->get_component<circle_collider*>(2)->set_radius(0.25);
}

void gas_item::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_GENERATOR) {
		generator* g = e->get_component<generator*>(1);
		
		if (!g->is_on()) {	
			item_component* inv = get_engine().get_entity(3)->get_component<item_component*>(1);
			inv->remove_item(4);
			
			g->turn_on();
		}
	}
}