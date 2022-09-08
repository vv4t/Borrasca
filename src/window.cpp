#include "window.hpp"

loli::window::window(int width, int height, const char* title) {
	 if (!glfwInit()) {
		 std::cout << "Failed to initialize GLFW!" << std::endl;
		 return;
	 }
	 
	 glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	 
	 m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	 
	 if (!m_window) {
		 std::cout << "Failed to create GLFW window!" << std::endl;
		 return;
	 }
	 
	 glfwMakeContextCurrent(m_window);
	 
	 m_width = width;
	 m_height = height;
}

void loli::window::set_cursor_pos(float x, float y) {
	glfwSetCursorPos(m_window, x * m_width, y * m_height);
}

float loli::window::get_time() {
	return (float) glfwGetTime();
}

int loli::window::get_width() {
	return m_width;
}

int loli::window::get_height() {
	return m_height;
}

bool loli::window::loop() {
	glfwPollEvents();
	return !glfwWindowShouldClose(m_window);
}

void loli::window::swap_buffer() {
	glfwSwapBuffers(m_window);
}

void loli::window::close() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GLFWwindow* loli::window::get_window() {
	return m_window;
}