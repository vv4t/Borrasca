#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "core_engine.hpp"
#include "object_pool.hpp"
#include "transform.hpp"
#include <iostream>

namespace loli {
	class core_engine;
	class entity_component;
	
	class entity {
		private:
			core_engine* m_engine;
			transform m_transform;
			
			unsigned int m_type = 0;
			bool m_remove = false;
		
		public:
			object_pool<entity_component*> m_components;
			entity(core_engine* engine);
			
			void start();
			void tick();
			void render();
			void on_collide(entity* e);
			void on_gui();
			
			void remove();
			
			entity_component* add_component(entity_component* component);
			void remove_component(int i);
			void set_component(int i, entity_component* component);
			
			transform& get_transform();
			core_engine& get_engine();
			
			void set_type(unsigned int type);
			unsigned int get_type();
			
			template <class T>
			T get_component(int id) {
				T component = dynamic_cast<T>(*m_components.get(id));
				assert(component != nullptr && "invalid cast get_component");
				
				return component;
			}
	};
	
	class entity_component {
		private:
			entity* m_parent;
		
		protected:
			render_engine& get_render();
			core_engine& get_engine();
			transform& get_transform();
			camera& get_cam();
			
			unsigned int get_ticks();
		
		public:
			bool m_remove = false;
			
			~entity_component() {  }
		
			virtual void start() { }
			virtual void tick() { }
			virtual void render() { }
			virtual void on_collide(entity* e) { }
			virtual void on_gui() { }
			
			virtual void remove() { }
			
			void set_parent(entity* parent);
			entity* get_parent();
			
			template <class T>
			T get_component(int id) {
				return m_parent->get_component<T>(id);
			}
	};
}

#endif
