#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 u_transform;

void main() {
	gl_Position = u_transform * vec4(pos, 1.0);
}
