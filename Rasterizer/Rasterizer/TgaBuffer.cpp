#include "stdafx.h"
#include "TgaBuffer.h"


TgaBuffer::TgaBuffer()
{
}

TgaBuffer::~TgaBuffer()
{
}

bool TgaBuffer::writeToFile(Buffer buffer) {
	unsigned char header[18] = { 0 };
	header[2] = 2;
	header[12] = 1024		& 0xFF; //buffer.width
	header[13] = (1024 >> 8)	& 0xFF;
	header[14] = 1024		& 0xFF; //buffer.height
	header[15] = (1024 >> 8) & 0xFF;
	header[16] = 32;

	std::ofstream file("render.tga", std::ios::binary);
	std::ofstream file2("renderDepth.tga", std::ios::binary);
	if (!file) {
		return false;
	}

	file.write((const char*)&header, 18);
	file2.write((const char*)&header, 18);
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 1024; j++) {
			unsigned int color = buffer.color[((int)S_WIDTH * i) + j];
			file.write((const char*)&color, sizeof(unsigned int));
			unsigned int d = 255 - (255 * buffer.depth[((int)S_WIDTH * i) + j]);
			unsigned int depth = d + (d << 8) + (d << 16) + (d << 24);
			file2.write((const char*)&depth, sizeof(unsigned int));
		}
	}

	file.close();
	file2.close();

	return true;
}