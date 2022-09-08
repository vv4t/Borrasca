#include "uniform_buffer.hpp"

loli::uniform_buffer::uniform_buffer(unsigned int size, unsigned int id) {
	glGenBuffers(1, &m_ubo);
	
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	glBindBufferRange(GL_UNIFORM_BUFFER, id, m_ubo, 0, size);
}

loli::uniform_buffer::~uniform_buffer() {
	glDeleteBuffers(1, &m_ubo);
}

void loli::uniform_buffer::sub_data(void* data, unsigned int offset, unsigned int size) {
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}