#include "rock_component.hpp"

#include "break_particle.hpp"
#include "entity_type.hpp"

void rock_component::start() {
	m_rigid = get_component<rigid_body*>(0);
}

void rock_component::tick() {
	
}

void rock_component::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_PICKAXE) {
		get_parent()->remove();
		return;
	}
	
	rigid_body* rb = e->get_component<rigid_body*>(0);
	rb->set_velocity(loli::vec3());
}

void rock_component::remove() {
	// get_engine().get_sound_engine().play2D("assets/sound/rock.wav");
	
	loli::entity* e = get_engine().add_entity();
	e->get_transform().translate(get_transform().get_pos());
	e->add_component(new break_particle());
	e->start();
}
