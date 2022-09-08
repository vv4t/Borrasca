#pragma once

#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <vector>
#include "entity.hpp"

class director : public loli::entity_component {
	private:
		std::vector<loli::entity*> m_enemies;
		std::vector<loli::vec3> m_spawns;
		
		loli::entity* m_player;
	
	public:
		void start();
		void tick();
		
		void add_bat(loli::vec3 pos);
		void add_ghost(loli::vec3 pos);
		void add_golem(loli::vec3 pos);
		void add_boss(loli::vec3 pos);
		
		void add_spawn(loli::vec3 pos);
		
		std::vector<loli::entity*>& get_enemies();
		void remove(loli::entity* e);
};

#endif