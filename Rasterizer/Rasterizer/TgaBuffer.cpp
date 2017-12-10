#include "stdafx.h"
#include "TgaBuffer.h"


TgaBuffer::TgaBuffer()
{
}


TgaBuffer::~TgaBuffer()
{
}

bool TgaBuffer::save(Buffer buffer) {
	unsigned char header[18] = { 0 };
	header[2] = 2;
	header[12] = 256		& 0xFF; //buffer.width
	header[13] = (256 >> 8)	& 0xFF;
	header[14] = 256		& 0xFF; //buffer.height
	header[15] = (256 >> 8) & 0xFF;
	header[16] = 32;

	std::ofstream file("render.tga", std::ios::binary);
	std::ofstream file2("renderDepth.tga", std::ios::binary);
	if (!file) {
		return false;
	}

	file.write((const char*)&header, 18);
	file2.write((const char*)&header, 18);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			unsigned int color = buffer.color[((int)buffer.width * i) + j];
			file.write((const char*)&color, sizeof(unsigned int));
			unsigned int depthInt = 255 - (255 * buffer.depth[((int)buffer.width * i) + j]);
			unsigned int depth = depthInt + (depthInt << 8) + (depthInt << 16) + (depthInt << 24);
			file2.write((const char*)&depth, sizeof(unsigned int));
		}
	}

	file.close();
	file2.close();

	return true;
}