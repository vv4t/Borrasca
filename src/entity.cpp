#include "entity.hpp"

loli::entity::entity(loli::core_engine* engine) {
	m_engine = engine;
	m_transform = transform();
	m_components.alloc_block(10);
}

void loli::entity::start() {
	for (int i = 0; i < m_components.len(); i++)
		if (m_components.is_alloc(i))
			(*m_components.get(i))->start();
}

void loli::entity::tick() {
	for (int i = 0; i < m_components.len(); i++) {
		if (m_components.is_alloc(i)) {
			if ((*m_components.get(i))->m_remove) {
				delete (*m_components.get(i));
				m_components.remove(i);
				
				continue;
			}
			
			(*m_components.get(i))->tick();
			
			if (m_remove) {
				for (int j = 0; j < m_components.len(); j++)
					delete (*m_components.get(j));
				
				get_engine().remove_entity(this);
				
				return;
			}
		}
	}
}

void loli::entity::render() {
	for (int i = 0; i < m_components.len(); i++)
		if (m_components.is_alloc(i))
			(*m_components.get(i))->render();
}

void loli::entity::on_collide(loli::entity* e) {
	for (int i = 0; i < m_components.len(); i++)
		if (m_components.is_alloc(i))
			(*m_components.get(i))->on_collide(e);
}

void loli::entity::on_gui() {
	for (int i = 0; i < m_components.len(); i++)
		if (m_components.is_alloc(i))
			(*m_components.get(i))->on_gui();
}

void loli::entity::remove() {
	for (int i = 0; i < m_components.len(); i++) {
		if (m_components.is_alloc(i)) {
			(*m_components.get(i))->remove();
		}
	}
	
	m_remove = true;
}

loli::entity_component* loli::entity::add_component(loli::entity_component* component) {
	m_components.add(component);
	component->set_parent(this);
	
	return component;
}

void loli::entity::remove_component(int i) {
	(*m_components.get(i))->remove();
	(*m_components.get(i))->m_remove = true;
}

void loli::entity::set_component(int i, loli::entity_component* component) {
	component->set_parent(this);
	m_components.set(i, component);
}

void loli::entity::set_type(unsigned int type) {
	m_type = type;
}

unsigned int loli::entity::get_type() {
	return m_type;
}

loli::transform& loli::entity::get_transform() {
	return m_transform;
}

loli::core_engine& loli::entity::get_engine() {
	return *m_engine;
}





loli::core_engine& loli::entity_component::get_engine()  {
	return m_parent->get_engine();
}

loli::camera& loli::entity_component::get_cam() {
	return get_engine().get_render_engine().get_cam();
}

loli::render_engine& loli::entity_component::get_render() {
	return get_engine().get_render_engine();
}

loli::transform& loli::entity_component::get_transform() {
	return get_parent()->get_transform();
}

unsigned int loli::entity_component::get_ticks() {
	return get_engine().get_ticks();
}

void loli::entity_component::set_parent(loli::entity* parent) {
	m_parent = parent;
}

loli::entity* loli::entity_component::get_parent() {
	return m_parent;
}
