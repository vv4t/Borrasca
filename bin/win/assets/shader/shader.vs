#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform vec2 u_uv_size;
uniform vec2 u_uv_offset;
uniform mat4 u_transform;
uniform mat4 u_light_mat;
uniform mat4 u_model;

out vec2 vs_uv;
out vec3 vs_pos;
out vec3 vs_normal;
out vec4 vs_shadow_pos;

void main() {
	vec4 screen_pos = u_transform * vec4(pos, 1.0);
	
	vs_pos = vec3(u_model * vec4(pos, 1.0));
	vs_normal = mat3(transpose(inverse(u_model))) * normal;
	vs_uv = u_uv_offset + uv * u_uv_size;
	vs_shadow_pos = u_light_mat * vec4(pos + vs_normal * 0.01, 1.0);
	
	gl_Position = screen_pos;
}