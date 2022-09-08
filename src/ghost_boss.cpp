#include "ghost_boss.hpp"

#include "ghost_projectile.hpp"
#include "break_particle.hpp"
#include "generator.hpp"

void ghost_boss::start() {
	m_player = get_engine().get_entity(2);
	m_sprite = get_component<sprite_render*>(2);
	m_rigid = get_component<rigid_body*>(0);
	m_health = get_component<health*>(4);
	m_director = get_engine().get_entity(5)->get_component<director*>(0);
	
	m_sprite->get_uv_offset().set_x(3);
	m_sprite->get_uv_offset().set_y(0);
	
	m_sprite->get_uv_size().set_x(2.0);
	m_sprite->get_uv_size().set_y(2.0);
}

void ghost_boss::shoot_spike(float dir) {
	loli::entity* proj = get_engine().add_entity();
	
	proj->add_component(new rigid_body());
	proj->add_component(new ghost_projectile(dir, 6.0, 100, 8));
	proj->add_component(new sprite_render(loli::vec2(7, 4)));
	proj->add_component(new circle_collider(0.1));
	
	proj->get_component<sprite_render*>(2)->is_rotate(true);
	
	proj->get_transform().translate(get_transform().get_pos());
	proj->get_transform().set_scale(loli::vec3(1.5, 1.5, 1.0));
	proj->get_transform().rotate(dir - 45.0 * M_PI / 180.0);
	proj->start();
}

void ghost_boss::shoot_orb(float dir) {
	loli::entity* proj = get_engine().add_entity();
	
	proj->add_component(new rigid_body());
	proj->add_component(new ghost_projectile(dir, 8.0, 100, 5));
	proj->add_component(new sprite_render(loli::vec2(7, 5)));
	proj->add_component(new circle_collider(0.1));
	
	proj->get_component<sprite_render*>(2)->is_rotate(true);
	
	proj->get_transform().translate(get_transform().get_pos());
	proj->get_transform().set_scale(loli::vec3(1.5, 1.5, 1.0));
	proj->get_transform().rotate(dir - 45.0 * M_PI / 180.0);
	proj->start();
}

void ghost_boss::tick() {
	float speed = 3;
	
	if (m_health->get_health() <= 0) {
		get_parent()->remove();
		return;
	}
	
	loli::vec3 d = m_player->get_transform().get_pos() - get_transform().get_pos();
	
	if (d.length() > 20) return;
	
	if (get_ticks() % 20 == 0)
		m_health->remove_hp(2 * generator::on);
	
	if (get_ticks() % 180 == 0)
		std::cout << "BOSS HEALTH: " << m_health->get_health() << std::endl;
	
	float dir = atan2(d.get_y(), d.get_x());
	
	if (get_ticks() % 300 == 0 && m_director->get_enemies().size() < 5) {
		m_director->add_ghost(get_transform().get_pos());
	}
	
	if (get_ticks() % 60 == 0) {
		for (int i = -1; i < 2; i++) {
			shoot_spike(dir + i * M_PI / 180 * 30);
		}
	}
	
	if (get_ticks() % 300 < 120) {
		if (get_ticks() % 10 == 0) {
			for (int i = 0; i < 4; i++) {
				shoot_orb(dir + (i * 90 + (get_ticks() * 20)) * M_PI / 180);
			}
		}
	}
}

void ghost_boss::remove() {
	m_director->remove(get_parent());
	
	loli::entity* e = get_engine().add_entity();
	e->get_transform().translate(get_transform().get_pos());
	e->add_component(new break_particle());
	e->start();
}