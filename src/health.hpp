#pragma once

#ifndef HEALTH_H
#define HEALTH_H

#include "entity.hpp"

class health : public loli::entity_component {
	private:
		int m_health;
		int m_max_health;
	
	public:
		health(int health, int max_health) {
			m_health = health;
			m_max_health = max_health;
		}
		
		void add_hp(int i) {
			if (m_health + i > m_max_health)
				m_health = m_max_health;
			else m_health += i;
		}
		void remove_hp(int i) {
			if (m_health - i < 0)
				m_health = 0;
			else m_health -= i;
		}
		
		int get_health() { return m_health; }
		int get_max_health() { return m_max_health; }
};

#endif