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
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			color[((int)width * j) + i] = (unsigned int)1.0f;
		}
	}
}

void Buffer::clearDepth()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			depth[((int)width * j) + i] = (unsigned int)1.0f;
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
	this->depth[((int)width * (int)y) + (int)x] = d;
	this->color[((int)width * (int)y) + (int)x] = _c.value;
}


