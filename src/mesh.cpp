#include "mesh.hpp"

#include <stdlib.h>
#include <string.h>
#include <iostream>

loli::mesh::mesh() {
	glGenVertexArrays(1, &m_vao);
}

loli::mesh::~mesh() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

loli::mesh& loli::mesh::init(vertex* vertices, int size) {
	char* vertbuf = vertices == nullptr ? nullptr : to_buffer(vertices, size);
	
	bind();
	
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, size * VERTEX_SIZE, vertbuf, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, NULL);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (char*) 0 + 12);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (char*) 0 + 24);
	glEnableVertexAttribArray(2);
	
	unbind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	m_vertex_size = size;
	
	delete vertbuf;
	
	return *this;
}

loli::mesh& loli::mesh::index(unsigned int* indices, int size) {
	bind();
	
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
	
	unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	m_element_size = size;
	
	return *this;
}

void loli::mesh::sub_vertices(vertex* vertices, unsigned int offset, unsigned int size) {
	char* vertbuf = to_buffer(vertices, size);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size * VERTEX_SIZE, vertbuf);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	delete vertbuf;
}

void loli::mesh::sub_indices(unsigned int* indices, unsigned int offset, unsigned int size) {
	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * sizeof(unsigned int), indices);
	
	unbind();
}

void loli::mesh::bind() {
	glBindVertexArray(m_vao);
}

void loli::mesh::unbind() {
	glBindVertexArray(0);
}

char* loli::mesh::to_buffer(vertex* vertices, int size) {
	char* vertbuf = (char*) malloc(VERTEX_SIZE * size);
	
	for (int i = 0; i < size; i++) {
		memcpy(&vertbuf[i * VERTEX_SIZE + 0], &vertices[i].get_pos()[0], 12);
		memcpy(&vertbuf[i * VERTEX_SIZE + 12], &vertices[i].get_normal()[0], 12);
		memcpy(&vertbuf[i * VERTEX_SIZE + 24], &vertices[i].get_tex()[0], 8);
	}
	
	return vertbuf;
}

int loli::mesh::vertex_size() {
	return m_vertex_size;
}

int loli::mesh::element_size() {
	return m_element_size;
}