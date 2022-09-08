#include "camera.hpp"

loli::camera::camera() {
	
}

void loli::camera::set_projection(loli::mat4 m) {
	m_projection = m;
}

loli::mat4 loli::camera::to_projected_view(mat4 m) {
	loli::mat4 rotation = loli::mat4().rotate_z(m_transform.get_rot() * -1);
	loli::mat4 translation = loli::mat4().translate(m_transform.get_pos() * -1);
	
	return m_projection * rotation * translation * m;
}

loli::transform& loli::camera::get_transform() {
	return m_transform;
}

loli::mat4& loli::camera::get_proj() {
	return m_projection;
}