#version 330 core

in vec2 uv;

out vec4 frag_color;

uniform sampler2D sampler;
uniform vec3 u_color;

void main() {
	frag_color = texture2D(sampler, uv) * vec4(u_color, 1.0);
}
