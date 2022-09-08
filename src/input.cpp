#include "input.hpp"

bool loli::input::m_mouse[2];
bool loli::input::m_keyboard[349];

int loli::input::m_width;
int loli::input::m_height;

float loli::input::m_mouse_x;
float loli::input::m_mouse_y;

void loli::input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) m_keyboard[key] = true;
	if (action == GLFW_RELEASE) m_keyboard[key] = false;
}

void loli::input::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) m_mouse[0] = 1;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) m_mouse[1] = 1;
	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) m_mouse[0] = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) m_mouse[1] = 0;
}

void loli::input::mousemove_callback(GLFWwindow* window, double xpos, double ypos) {
	m_mouse_x = +((float) xpos / (float) m_width - 0.5f);
	m_mouse_y = -((float) ypos / (float) m_height - 0.5f);
}
bool loli::input::get_key(int key) {
	return m_keyboard[key];
}

bool loli::input::get_mouse(int mouse) {
	return m_mouse[mouse];
}

float loli::input::get_mouse_x() {
	return m_mouse_x;
}

float loli::input::get_mouse_y() {
	return m_mouse_y;
}

void loli::input::init(loli::window* window) {
	glfwSetKeyCallback(window->get_window(), loli::input::key_callback);
	glfwSetMouseButtonCallback(window->get_window(), loli::input::mouse_callback);
	glfwSetCursorPosCallback(window->get_window(), loli::input::mousemove_callback);
	
	m_width = window->get_width();
	m_height = window->get_height();
}