#include "player_gui.hpp"

void player_gui::start() {
	m_health = get_component<health*>(5);
}

void player_gui::tick() {
	if (m_health->get_health() == 0) {
		exit(0);
	}
}

void player_gui::on_gui() {
	if (m_health->get_health() == 0) {
		get_render().gui_img(2, loli::vec2(0, 0), loli::vec2(80, 60), loli::vec2(), loli::vec2(1.0, 1.0));
	} else {
		float health_size = (float) m_health->get_health() / (float) m_health->get_max_health() * 40;
		
		get_render().get_shader()->uniform_vec3("u_color", loli::vec3(1.0, 0.0, 0.0));
		get_render().gui_img(0, loli::vec2(5, 55), loli::vec2(health_size, 2), loli::vec2(6, 7) * loli::vec2(1.0 / 16.0, 1.0 / 16.0), loli::vec2(1.0, 1.0));
	}
}