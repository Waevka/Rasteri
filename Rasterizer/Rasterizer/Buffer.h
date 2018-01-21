#pragma once

static const int S_WIDTH = 1024;
static const int S_HEIGHT = 1024;

class Buffer
{
public:
	unsigned int *color;
	float* depth;
	float width, height, minx, maxx, miny, maxy, len;

	Buffer();
	Buffer(int w, int h);
	~Buffer();
	void setSize(int w, int h);
	void clearColor();
	void clearDepth();
	void clear();
	void writeColor(float x, float y, WColor _c, float d);
};

