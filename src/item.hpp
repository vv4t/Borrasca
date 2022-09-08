#pragma once

#ifndef ITEM_H
#define ITEM_H

#include "entity.hpp"
#include "sprite_render.hpp"
#include "character_controller.hpp"
#include "texture.hpp"

class item_component;

class item : public loli::entity_component {
	private:
		item_component* m_item;
		sprite_render* m_sprite;
		character_controller* m_char;
		
		loli::vec2 m_spr_pos;
		
		int get_state();
		int get_frame();
		
		int m_count = 0;
	
	protected:
		sprite_render& get_sprite();
		item_component& get_item();
		character_controller& get_char();
		
		void set_spr(loli::vec2 offset);
	
	public:
		virtual void init();
		void tick();
		
		virtual void equip();
		virtual void unequip() { }
		
		loli::vec2 get_spr();
		
		void set_count(int i);
		int get_count();
};

class item_component : public loli::entity_component {
	private:
		loli::entity* m_player;
		character_controller* m_char;
		sprite_render* m_sprite;
		
		std::vector<item*> m_inventory;
		item* m_current_item = nullptr;
		
		loli::texture* m_gui;
		
		void offset_item();
		
	public:
		loli::vec2 m_offset;
		loli::vec2 m_size;
		
		void add_item(item* _item);
		void equip(int item);
		
		void start();
		void tick();
		
		void on_gui();
		
		int item_count();
		void remove_item(int i);
		item* get_item(int i);
};

#endif