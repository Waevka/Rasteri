#pragma once
class Buffer
{
public:
	unsigned int color;
	float depth;
	float width, height, minx, maxx, miny, maxy, len;

	Buffer();
	~Buffer();
	void setSize(int size);
	void clearColor();
	void clearDepth();
};

