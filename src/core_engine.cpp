#include "core_engine.hpp"

loli::core_engine::core_engine(loli::window* win) {
	m_win = win;
	
	m_render_engine = new render_engine();
	// m_sound_engine = irrklang::createIrrKlangDevice();
	m_entity_pool.alloc_block(500);
}

loli::core_engine::~core_engine() {
	delete m_render_engine;
}

void loli::core_engine::start() {
	m_start = true;
	
	for (int i = 0; i < m_entity_pool.len(); i++) {
		if (m_entity_pool.is_alloc(i)) {
			m_entity_pool.get(i)->start();
		}
	}
}

void loli::core_engine::run() {
	float seconds_per_tick = 1.0f / 60.0f;
	float previous_time = 0;
	float unprocessed_time = 0.0f;
	
	unsigned int frames = 0;
	
	while (m_win->loop()) {
		float current_time = m_win->get_time();
		float elapsed_time = current_time - previous_time;
		previous_time = current_time;
		
		unprocessed_time += elapsed_time;
		
		while (unprocessed_time >= 0.0f) {
			unprocessed_time -= seconds_per_tick;
			
			if (m_ticks % 60 == 0) {
				std::cout << "frames: " << frames << std::endl;
				frames = 0;
			}
			
			tick();
			m_ticks++;
		}
		
		m_render_engine->clear();
		render();
		
		m_win->swap_buffer();
		frames++;
	}
}

void loli::core_engine::tick() {
	for (int i = 0; i < m_entity_pool.len(); i++) {
		if (m_entity_pool.is_alloc(i)) {
			m_entity_pool.get(i)->tick();
		}
	}
	
	m_render_engine->get_light().update_lights();
}

void loli::core_engine::render() {
	m_render_engine->bind_texture(0, 0);
	m_render_engine->bind_shader(0);
	
	for (int i = 0; i < m_entity_pool.len(); i++)
		if (m_entity_pool.is_alloc(i))
			m_entity_pool.get(i)->render();
	
	glDisable(GL_DEPTH_TEST);
	m_render_engine->bind_mesh(0);
	m_render_engine->bind_shader(2);
	
	for (int i = 0; i < m_entity_pool.len(); i++)
		if (m_entity_pool.is_alloc(i))
			m_entity_pool.get(i)->on_gui();
	
	glEnable(GL_DEPTH_TEST);
}

loli::entity* loli::core_engine::add_entity() {
	return new (m_entity_pool.alloc()) entity(this);
}

loli::entity* loli::core_engine::get_entity(unsigned int id) {
	return m_entity_pool.get(id);
}

void loli::core_engine::remove_entity(loli::entity* e) {
	m_entity_pool.remove(e);
}

unsigned int loli::core_engine::get_ticks() {
	return m_ticks;
}

loli::render_engine& loli::core_engine::get_render_engine() {
	return *m_render_engine;
}

bool loli::core_engine::started() {
	return m_start;
}
/*
irrklang::ISoundEngine& loli::core_engine::get_sound_engine() {
	return *m_sound_engine;
}
*/
