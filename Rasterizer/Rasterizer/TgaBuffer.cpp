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
	if (!file) {
		return false;
	}

	file.write((const char*)&header, 18);
	for (unsigned short i = 0; i < 256; i++) {
		for (unsigned short j = 0; j < 256; j++) {
			unsigned int color = 0xFFFFFF - j;
			file.write((const char*)&color, sizeof(unsigned int));
		}
	}

	file.close();

	return true;
}