#pragma once

#ifndef CRATE_COMPONENT_H
#define CRATE_COMPONENT_H

#include "rigid_body.hpp"
#include "entity_type.hpp"

class crate_component : public loli::entity_component {
	private:
		rigid_body* m_rigid;
		
	public:
		void start();
		void remove();
		
		void on_collide(loli::entity* e);
};

#endif