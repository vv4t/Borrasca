#include "bitmap.hpp"

loli::bitmap::bitmap(unsigned char* data, unsigned int width, unsigned int height) {
	m_data = data;
	m_width = width;
	m_height = height;
}

loli::bitmap::~bitmap() {
	delete m_data;
}

unsigned int loli::bitmap::get_width() {
	return m_width;
}

unsigned int loli::bitmap::get_height() {
	return m_height;
}

unsigned char loli::bitmap::get(unsigned int i) {
	return m_data[i];
}

unsigned char& loli::bitmap::operator[](unsigned int i) {
	return m_data[i];
}