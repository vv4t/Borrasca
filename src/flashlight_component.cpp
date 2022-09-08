#include "flashlight_component.hpp"

#include "input.hpp"
#include "entity_type.hpp"
#include "health.hpp"

void flashlight_component::start() {
	m_player = get_engine().get_entity(2);
	m_director = get_engine().get_entity(5)->get_component<director*>(0);
	m_radius = 7;
}

void flashlight_component::tick() {
	float rot = get_cam().get_transform().get_rot();
	float ang_max = M_PI * 2;
	
	float dx = loli::input::get_mouse_x();
	float dy = loli::input::get_mouse_y();
	
	float dir = atan2(dy, dx);
	
	float a = dir + rot;
	float b = fmod(a - m_dir, ang_max);
	float c = fmod(2 * b, ang_max) - b;
	
	m_dir += c / 10;
	
	if (get_ticks() % 10 == 0)
		m_radius *= 0.999;
	
	loli::vec3 pos = m_player->get_transform().get_pos();
	
	get_render().get_light().get_light(0)->set_pos(pos + loli::vec3(0.0, 0.5).rotate(rot));
	get_render().get_light().get_light(0)->set_dir(m_dir);
	get_render().get_light().get_light(0)->set_intensity(m_radius);
	
	get_transform().set_rot(dir + rot);
	get_transform().set_pos(pos + loli::vec3(dx, dy).normalize().rotate(rot) * 1.5);
	
	if (get_ticks() % 30 == 0) {
		for (int i = 0; i < m_director->get_enemies().size(); i++) {
			if (m_director->get_enemies()[i]->get_type() == ENTITY_GHOST || m_director->get_enemies()[i]->get_type() == ENTITY_BOSS) {
				loli::entity* e = m_director->get_enemies()[i];
				
				loli::vec3 d0 = get_transform().get_pos() - m_player->get_transform().get_pos();
				loli::vec3 d1 = e->get_transform().get_pos() - m_player->get_transform().get_pos();
				
				if (d1.length() > m_radius) continue;
				
				float angle = acos(d0.normalize().dot(d1.normalize()));
				
				if (angle < 0.5) {
					if (e->get_type() == ENTITY_GHOST) {
						int type = get_parent()->get_type();
						
						get_parent()->set_type(ENTITY_FLASHLIGHT);
						
						e->on_collide(get_parent());
						e->get_component<health*>(6)->remove_hp(3);
						
						get_parent()->set_type(type);
					} else {
						e->get_component<health*>(4)->remove_hp(3);
					}
				}
			}
		}
	}
}

void flashlight_component::on_collide(loli::entity* e) {
	get_engine().get_entity(3)->on_collide(e);
}

void flashlight_component::on_gui() {
	get_render().get_shader()->uniform_vec3("u_color", loli::vec3(1.0, 1.0, 0.0));
	
	get_render().gui_img(
		0,
		loli::vec2(5, 52),
		loli::vec2(m_radius / 7.0 * 40, 2),
		loli::vec2(6, 7) * loli::vec2(1.0 / 16.0, 1.0 / 16.0),
		loli::vec2(1.0, 1.0)
	);
}

void flashlight_component::add_power(float f) {
	if (m_radius + f > 7) m_radius = 7;
	m_radius += f;
}