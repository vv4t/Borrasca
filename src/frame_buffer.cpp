#include "frame_buffer.hpp"

loli::frame_buffer::frame_buffer(int width, int height) {
	m_width = width;
	m_height = height;
	
	glGenTextures(1, &m_frame);
	glBindTexture(GL_TEXTURE_2D, m_frame);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_frame, 0);
	
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

loli::frame_buffer::~frame_buffer() {
	glDeleteBuffers(1, &m_fbo);
	glDeleteTextures(1, &m_fbo);
}

void loli::frame_buffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void loli::frame_buffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void loli::frame_buffer::bind_frame(int sampler) {
	glActiveTexture(GL_TEXTURE0 + sampler);
	glBindTexture(GL_TEXTURE_2D, m_frame);
}

int loli::frame_buffer::get_width() {
	return m_width;
}

int loli::frame_buffer::get_height() {
	return m_height;
}