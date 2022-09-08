#include "menu_component.hpp"

#include "input.hpp"

menu_component::menu_component(game* a) {
	g = a;
}

void menu_component::tick() {
	if (loli::input::get_key(loli::input::KEY_R)) {
		g->clean();
		g->init_game();
	}
}

void menu_component::on_gui() {
}