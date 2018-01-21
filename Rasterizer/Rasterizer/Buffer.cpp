#include "stdafx.h"
#include "Buffer.h"


Buffer::Buffer()
{
	width = 1024;
	height = 1024;
	color = new unsigned int[1024 * 1024];
	depth = new float[1024 * 1024];
	clear();
}

Buffer::Buffer(int w, int h)
{
	width = (float)w;
	height = (float)h;
	color = new unsigned int[w*h];
	depth = new float[w*h];
	clear();
}


Buffer::~Buffer()
{
}

void Buffer::setSize(int w, int h)
{
	width = (float)w;
	height = (float)h;
	if (color != NULL) {
		delete[] color;
	}
	if (depth != NULL) {
		delete[] depth;
	}
	color = new unsigned int[w*h];
	depth = new float[w*h];
	clear();
}

void Buffer::clearColor()
{
	for (int i = 0; i < S_WIDTH; i++) {
		for (int j = 0; j < S_HEIGHT; j++) {
			color[((int)S_WIDTH * j) + i] = (unsigned int)1.0f;
		}
	}
}

void Buffer::clearDepth()
{
	for (int i = 0; i < S_WIDTH; i++) {
		for (int j = 0; j < S_HEIGHT; j++) {
			depth[((int)S_WIDTH * j) + i] = (unsigned int)1.0f;
		}
	}
}

void Buffer::clear()
{
	clearColor();
	clearDepth();
}

void Buffer::writeColor(float x, float y, WColor _c, float d)
{
	this->depth[((int)S_WIDTH * (int)y) + (int)x] = d;
	this->color[((int)S_WIDTH * (int)y) + (int)x] = _c.value;
}


