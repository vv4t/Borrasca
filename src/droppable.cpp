#include "droppable.hpp"

#include "health.hpp"
#include "entity_type.hpp"
#include "flashlight_component.hpp"
#include "item.hpp"
#include "flare_gun_item.hpp"
#include "gas_item.hpp"

droppable::droppable(int type) {
	m_type = type;
}

void droppable::start() {
	m_rigid = get_component<rigid_body*>(0);
	m_sprite = get_component<sprite_render*>(2);
	
	m_sprite->get_uv_offset().set_x(m_type + 4);
	m_sprite->get_uv_offset().set_y(8);
}

void droppable::tick() {
	
}

void droppable::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_PLAYER) {
		switch (m_type) {
			case 1: {
				get_engine().get_entity(2)->get_component<health*>(5)->add_hp(20);
			}; break;
			
			case 2: {
				get_engine().get_entity(4)->get_component<flashlight_component*>(1)->add_power(0.5);
			}; break;
			
			case 3: {
				item* flare_gun = get_engine().get_entity(3)->get_component<item_component*>(1)->get_item(2);
				if (flare_gun->get_count() >= 6) return;
				flare_gun->set_count(flare_gun->get_count() + 1);
			}; break;
			
			case 4: {
				item_component* inv = get_engine().get_entity(3)->get_component<item_component*>(1);
				
				if (inv->item_count() < 5) {
					inv->add_item(new gas_item());
				} else {
					return;
				}
			};
		};
		
		// get_engine().get_sound_engine().play2D("assets/sound/pickup.wav");
		
		get_parent()->remove();
	}
}
