#version 330 core

in vec2 vs_uv;
in vec3 vs_pos;
in vec3 vs_normal;
in vec4 vs_screen_pos;
in vec4 vs_shadow_pos;

out vec4 frag_color;

struct light {
	vec3 m_pos;
	float m_intensity;
	
	vec3 m_col;
	float m_dir;
	
	float m_angle;
	int m_shadow;
};

layout (std140) uniform u_lightbuf {
	int m_light_count;
	float m_ambience;
	
	light m_lights[30];
};

uniform vec3 u_color;
uniform sampler2D u_sampler;
uniform sampler2D u_depth;
uniform float u_clamp;

float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	vec4 color = texture2D(u_sampler, vs_uv);
	if (color.w == 0) discard;
	
	vec3 light = vec3(0, 0, 0);
	
	vec3 projcoords = vs_shadow_pos.xyz / vs_shadow_pos.w;
	projcoords = projcoords * 0.5 + 0.5;
	
	vec4 a = texture2D(u_depth, projcoords.xy);
	
	for (int i = 0; i < m_light_count; i++) {
		if (m_lights[i].m_intensity <= 0) continue;
		
		vec2 to_light = m_lights[i].m_pos.xy - vs_pos.xy;
		
		float d = max(m_lights[i].m_intensity - length(to_light), 0.0) / m_lights[i].m_intensity * 7;
		float attuention = d * d * 0.05 + d * 0.02;
		
		vec2 frag_dir = normalize(to_light);
		vec2 light_dir = normalize(vec2(cos(m_lights[i].m_dir), sin(m_lights[i].m_dir)));
		
		float diffuse = dot(frag_dir, vs_normal.xy);
		float angle = dot(-frag_dir, light_dir);
		
		if (diffuse < 0 || vs_pos.z == 1) attuention = 0;
		if (acos(angle) > m_lights[i].m_angle) attuention = 0;
		if (m_lights[i].m_shadow > 0)
			if (a.x > 0.6) attuention = 0;
		
		if (color.x == 1.0 && floor(color.y * 100) == 10) attuention = 1;
		
		light += m_lights[i].m_col * attuention;
	}
	
	if (u_clamp > 0.0) light = clamp(light, 0.0, 1.0);
	else light = clamp(light, 0.0, 2.0);
	
	frag_color = vec4(vec3(m_ambience + light), 1.0) * color * vec4(u_color, 1);
}