#include "shader.hpp"

#include <iostream>
#include <cstring>

loli::shader::shader(char* vs_src, char* fs_src) {
	m_program = glCreateProgram();
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_src, NULL);
	glCompileShader(vs);
	
	int success;
	char infolog[256];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infolog);
		
		std::cout << "ERROR IN VERTEX SHADER" << std::endl;
		std::cout << infolog << std::endl;
	}
	
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_src, NULL);
	glCompileShader(fs);
	
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(fs, 512, NULL, infolog);
		
		std::cout << "ERROR in FRAGMENT SHADER" << std::endl;
		std::cout << infolog << std::endl;
	}
	
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	
	glLinkProgram(m_program);	

	glDetachShader(m_program, vs);
	glDetachShader(m_program, fs);
	
	glDeleteShader(vs);
	glDeleteShader(fs);
	
	load_uniforms();
	
	delete[] vs_src;
	delete[] fs_src;
}

void loli::shader::load_uniforms() {
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &m_uniform_count);
	
	m_uniform_names = (char**) malloc(m_uniform_count * sizeof(char*));
	m_uniform_locations = (GLuint*) malloc(m_uniform_count * sizeof(GLuint));
	
	for (int i = 0; i < m_uniform_count; i++) {
		char name[32];
		int name_len;
		int size;
		GLenum type;
		
		glGetActiveUniform(m_program, i, 31, &name_len, &size, &type, name);
		
		m_uniform_names[i] = (char*) malloc(name_len + 1);
		m_uniform_names[i][name_len] = 0x00;
		memcpy(m_uniform_names[i], &name[0], name_len);
		
		m_uniform_locations[i] = glGetUniformLocation(m_program, name);
	}
}

GLuint loli::shader::get_uniform_location(char* name) {
	for (int i = 0; i < m_uniform_count; i++) {
		if (strcmp(name, m_uniform_names[i]) == 0)
			return m_uniform_locations[i];
	}
	
	// std::cout << "COULD NOT FIND UNIFORM LOCATION: " << name << std::endl;
	
	return -1;
}

void loli::shader::uniform_int(char* name, int i) {
	GLuint location = get_uniform_location(name);
	glUniform1i(location, i);
}

void loli::shader::uniform_float(char* name, float f) {
	GLuint location = get_uniform_location(name);
	glUniform1f(location, f);
}

void loli::shader::uniform_vec2(char* name, vec2 v) {
	GLuint location = get_uniform_location(name);
	glUniform2f(location, v.get_x(), v.get_y());
}

void loli::shader::uniform_vec3(char* name, vec3 v) {
	GLuint location = get_uniform_location(name);
	glUniform3f(location, v.get_x(), v.get_y(), v.get_z());
}

void loli::shader::uniform_mat4(char* name, mat4 m) {
	GLuint location = get_uniform_location(name);
	glUniformMatrix4fv(location, 1, GL_TRUE, &m.m[0]);
}

void loli::shader::uniform_block(char* name, unsigned int id) {
	GLuint location = glGetUniformBlockIndex(m_program, name);
	glUniformBlockBinding(m_program, location, id);
}

void loli::shader::bind() {
	glUseProgram(m_program);
}

void loli::shader::dispose() {
	glDeleteProgram(m_program);
	
	delete m_uniform_locations;
	
	for (int i = 0; i < m_uniform_count; i++)
		delete m_uniform_names[i];
	
	delete m_uniform_names;
}