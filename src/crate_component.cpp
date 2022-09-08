#include "crate_component.hpp"

#include "break_particle.hpp"
#include "droppable.hpp"
#include "rigid_body.hpp"
#include "circle_collider.hpp"
#include "terrain_collider.hpp"

void crate_component::start() {
	m_rigid = get_component<rigid_body*>(0);
}

void crate_component::on_collide(loli::entity* e) {
	if (e->get_type() == ENTITY_DROPPABLE) {
		return;
	}
	
	if (e->get_type() == ENTITY_PICKAXE) {
		get_parent()->remove();
		return;
	}
	
	rigid_body* rb = e->get_component<rigid_body*>(0);
	rb->set_velocity(loli::vec3());
}

void crate_component::remove() {
	// get_engine().get_sound_engine().play2D("assets/sound/crate.wav");
	
	loli::entity* e = get_engine().add_entity();
	e->get_transform().translate(get_transform().get_pos());
	e->add_component(new break_particle());
	e->start();
	
	int num = 1 + rand() % 3;
	
	for (int i = 0; i < num; i++) {
		loli::entity* e = get_engine().add_entity();
		e->add_component(new rigid_body());
		e->add_component(new droppable(rand() % 4));
		e->add_component(new sprite_render());
		e->add_component(new terrain_collider());
		e->add_component(new circle_collider(0.5));
		e->get_transform().translate(get_transform().get_pos());
		e->get_transform().set_scale(loli::vec3(0.5, 0.5, 1.0));
		e->set_type(ENTITY_DROPPABLE);
		e->start();
		
		rigid_body* rb = e->get_component<rigid_body*>(0);
		rb->accelerate(loli::vec3(rand() % 10 - 5, rand() % 10 - 5).normalize(), 5, 5);
		rb->is_grounded(true);
	}
}
