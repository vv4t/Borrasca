#include "assetlib.hpp"

#include "math3d.hpp"
#include "lodepng.hpp"
#include "vertex.hpp"

char* loli::assetlib::load_file(char* path) {
	if (m_files.count(std::string(path)) > 0) return m_files[std::string(path)];
	
	FILE* fs = fopen(path, "rb");
	
	if (!fs) {
		std::cout << "Failed to open " << path << std::endl;
		return NULL;
	}
	
	fseek(fs, 0L, SEEK_END);
	long length = ftell(fs);
	
	fseek(fs, 0L, SEEK_SET);
	
	char* content = (char*) malloc(length + 1);
	fread(content, 1, length, fs);
	
	fclose(fs);
	content[length] = 0x00;
	
	m_files[std::string(path)] = content;
	
	return content;
}

loli::bitmap* loli::assetlib::load_bitmap(char* path) {
	if (m_bitmaps.count(std::string(path)) > 0) return m_bitmaps[std::string(path)];
	
	unsigned char* data;
	unsigned int width, height;
	
	if (lodepng_decode32_file(&data, &width, &height, path)) {
		std::cout << "Failed to open " << path << std::endl;
		
		return NULL;
	}
	
	loli::bitmap* bmp = new bitmap(&data[0], width, height);
	
	m_bitmaps[std::string(path)] = bmp;
	
	return bmp;
}