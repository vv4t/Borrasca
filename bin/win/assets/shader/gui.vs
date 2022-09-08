#version 330 core

layout(location = 0) in vec3 vertices;
layout(location = 2) in vec2 texcoords;

out vec2 uv;

uniform vec2 u_pos;
uniform vec2 u_size;

uniform vec2 u_uv_pos;
uniform vec2 u_uv_size;

uniform vec3 u_col;

void main() {
	uv = u_uv_pos + texcoords * u_uv_size;
	
	gl_Position = vec4((vec3(u_pos - 0.5 + u_size / 2, 0) + vertices * vec3(u_size, 1)) * 2.0, 1);
}