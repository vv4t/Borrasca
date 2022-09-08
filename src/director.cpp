#include "director.hpp"

#include "rigid_body.hpp"
#include "terrain_collider.hpp"
#include "circle_collider.hpp"
#include "ghost_component.hpp"
#include "health.hpp"
#include "trail_particle.hpp"
#include "entity_type.hpp"
#include "bat_component.hpp"
#include "golem_component.hpp"
#include "emitter_particle.hpp"
#include "flamable.hpp"
#include "ghost_boss.hpp"

#include <algorithm>

void director::add_bat(loli::vec3 pos) {
	pos += loli::vec3(0.5, 0.5);
	loli::entity* bat = get_engine().add_entity();
	
	bat->add_component(new rigid_body());
	bat->add_component(new bat_component());
	bat->add_component(new sprite_render());
	bat->add_component(new terrain_collider());
	bat->add_component(new circle_collider(0.25));
	bat->set_type(ENTITY_BAT);
	bat->start();
	
	bat->get_transform().translate(pos);
	m_enemies.push_back(bat);
}

void director::add_ghost(loli::vec3 pos) {
	pos += loli::vec3(0.5, 0.5);
	loli::entity* ghost = get_engine().add_entity();
	ghost->add_component(new rigid_body());
	ghost->add_component(new ghost_component());
	ghost->add_component(new sprite_render());
	ghost->add_component(new circle_collider(0.25));
	ghost->add_component(new terrain_collider());
	ghost->add_component(new trail_particle(ghost->get_component<rigid_body*>(0), 30, 20, 0.07));
	ghost->add_component(new health(50, 50));
	ghost->add_component(new emitter_particle());
	ghost->add_component(new flamable());
	ghost->get_component<trail_particle*>(5)->set_color(loli::vec3());
	ghost->get_component<emitter_particle*>(7)->set_color(loli::vec3(1.0, 0.5, 0.5));
	ghost->set_type(ENTITY_GHOST);
	ghost->start();
	
	ghost->get_transform().translate(pos);
	m_enemies.push_back(ghost);
}

void director::add_golem(loli::vec3 pos) {
	pos += loli::vec3(0.5, 0.5);
	loli::entity* golem = get_engine().add_entity();
	golem->add_component(new rigid_body());
	golem->add_component(new golem_component());
	golem->add_component(new sprite_render());
	golem->add_component(new circle_collider(0.6));
	golem->add_component(new terrain_collider());
	golem->add_component(new trail_particle(golem->get_component<rigid_body*>(0), 30, 20, 0.07));
	golem->add_component(new health(100, 100));
	golem->add_component(new emitter_particle());
	golem->add_component(new flamable());
	golem->get_component<trail_particle*>(5)->set_color(loli::vec3());
	golem->get_component<emitter_particle*>(7)->set_color(loli::vec3(1.0, 0.5, 0.5));
	golem->set_type(ENTITY_GHOST);
	golem->start();
	
	golem->get_transform().translate(pos);
	m_enemies.push_back(golem);
}

void director::add_boss(loli::vec3 pos) {
	pos += loli::vec3(0.5, 0.5);
	loli::entity* boss = get_engine().add_entity();
	boss->add_component(new rigid_body());
	boss->add_component(new ghost_boss());
	boss->add_component(new sprite_render());
	boss->add_component(new circle_collider(0.6));
	boss->add_component(new health(1000, 1000));
	boss->set_type(ENTITY_BOSS);
	boss->start();
	
	boss->get_transform().translate(pos);
	boss->get_transform().set_scale(loli::vec3(3, 3, 1.0));
	
	m_enemies.push_back(boss);
}

void director::add_spawn(loli::vec3 pos) {
	m_spawns.push_back(pos);
}

void director::start() {
	m_player = get_engine().get_entity(2);
}

void director::tick() {
	if (get_ticks() % (60 * 10) == 0 && m_enemies.size() < 7) {
		for (int i = 0; i < m_spawns.size(); i++) {
			float distance = (m_player->get_transform().get_pos() - m_spawns[i]).length();
			
			if (distance > 5 && distance < 40) {
				for (int j = 0; j < 3; j++) {
					int num = rand() % 100;
					
					if (num < 5)
						add_golem(m_spawns[i]);
					else if (num < 40)
						add_ghost(m_spawns[i]);
					else
						add_bat(m_spawns[i]);
					
					if (m_enemies.size() > 7) break;
				}
			}
			
		}
	}
}

std::vector<loli::entity*>& director::get_enemies() {
	return m_enemies;
}

void director::remove(loli::entity* e) {
	m_enemies.erase(
		std::remove(m_enemies.begin(), m_enemies.end(), e),
		m_enemies.end()
	);
}