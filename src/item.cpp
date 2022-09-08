#include "item.hpp"

#include "input.hpp"

float texel = 1 / 8.0;

void item::init() {
	m_sprite = get_component<sprite_render*>(0);
	m_item = get_component<item_component*>(1);
	m_char = get_engine().get_entity(2)->get_component<character_controller*>(1);
}

void item::equip() {
	set_spr(loli::vec2(m_spr_pos.get_x(), m_spr_pos.get_y()));
}

void item::tick() {
	
}

void item::set_spr(loli::vec2 v) {
	m_spr_pos = v;
}

sprite_render& item::get_sprite() {
	return *m_sprite;
}

item_component& item::get_item() {
	return *m_item;
}

character_controller& item::get_char() {
	return *m_char;
}

loli::vec2 item::get_spr() {
	return m_spr_pos;
}

void item::set_count(int i) {
	m_count = i;
}

int item::get_count() {
	return m_count;
}


void item_component::start() {
	m_player = get_engine().get_entity(2);
	m_char = m_player->get_component<character_controller*>(1);
	m_sprite = get_component<sprite_render*>(0);
}

void item_component::add_item(item* _item) {
	_item->set_parent(get_parent());
	_item->init();
	m_inventory.push_back(_item);
}

void item_component::equip(int i) {
	if (i > m_inventory.size()) return;
	if (m_current_item == m_inventory[i]) return;
	
	if (m_current_item != nullptr) {
		m_current_item->unequip();
	}
	
	m_current_item = m_inventory[i];
	
	get_parent()->set_component(2, m_current_item);
	m_current_item->equip();
}

void item_component::offset_item() {
	loli::vec3 pos_offset;
	
	int state = m_char->m_state;
	int frame = m_char->m_frame;
	
	float xpos = 0.5 + m_offset.get_x() * texel - 1.0 / 256.0;
	float ypos = m_offset.get_y() * texel;
	
	if (state == 0 || state == 2) {
		get_transform().set_scale(loli::vec3(m_size.get_x(), m_size.get_y(), 1));
		pos_offset.set_x(xpos);
	} else {
		get_transform().set_scale(loli::vec3(-m_size.get_x(), m_size.get_y(), 1));
		pos_offset.set_x(-xpos);
	}
	
	pos_offset.set_y(ypos);
	
	if (frame > 0) {
		if (frame == 1)
			pos_offset.set_x(pos_offset.get_x() - texel * (pos_offset.get_x() < 0 ? -1 : 1));
		
		if (state < 2 && frame == 2)
			pos_offset.set_y(pos_offset.get_y() - texel);
	}
	

	loli::vec3 pos = m_player->get_transform().get_pos() + pos_offset.rotate(m_player->get_transform().get_rot());
	
	get_transform().set_pos(pos);
}

void item_component::tick() {
	offset_item();
	
	if (loli::input::get_key(loli::input::KEY_1)) equip(0);
	if (loli::input::get_key(loli::input::KEY_2)) equip(1);
	if (loli::input::get_key(loli::input::KEY_3)) equip(2);
	if (loli::input::get_key(loli::input::KEY_4)) equip(3);
	if (loli::input::get_key(loli::input::KEY_5)) if (item_count() > 4) equip(4);
}

void item_component::on_gui() {
	get_render().get_shader()->uniform_vec3("u_color", loli::vec3(1.0, 1.0, 1.0));
	get_render().gui_img(1, loli::vec2(0, 0), loli::vec2(21.5, 4), loli::vec2(), loli::vec2(16.0, 16.0));
	
	for (int i = 0; i < 5; i++) {
		if (i < m_inventory.size()) {
			get_render().gui_img(
				0,
				loli::vec2(0.5 + 3.5 * i, 0.5),
				loli::vec2(3, 3),
				m_inventory[i]->get_spr() * loli::vec2(1.0 / 16, 1.0 / 16),
				loli::vec2(1.0, 1.0)
			);
			
			if (m_inventory[i]->get_count() > 0) {
				get_render().gui_img(
					0,
					loli::vec2(0.5 + 3.5 * i + 2, 2.0),
					loli::vec2(1.5, 1.5),
					loli::vec2(m_inventory[i]->get_count(), 9) * loli::vec2(1.0 / 16.0, 1.0 / 16.0),
					loli::vec2(1.0, 1.0)
				);
			}
		}
		
		get_render().gui_img(
			0,
			loli::vec2(0.5 + 3.5 * i, 0.5),
			loli::vec2(1.5, 1.5),
			loli::vec2(i + 1, 9) * loli::vec2(1.0 / 16.0, 1.0 / 16.0),
			loli::vec2(1.0, 1.0)
		);
	}
}

item* item_component::get_item(int i) {
	return m_inventory[i];
}

void item_component::remove_item(int i) {
	equip(0);
	m_inventory.erase(m_inventory.begin() + i);
}

int item_component::item_count() {
	return m_inventory.size();
}