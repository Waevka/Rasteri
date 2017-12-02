#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle()
{
	vert1 = WFloat3(0.0f, 0.0f, 0.0f);
	vert2 = WFloat3(2.0f, 0.0f, 0.0f);
	vert3 = WFloat3(1.0f, 1.0f, 0.0f);
	color = 0x000000;
}

Triangle::Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
	color = 0x000000;
}

Triangle::Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, unsigned int _color)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
	color = _color;
}


Triangle::Triangle(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{
	vert1 = WFloat3(x1, y1, z1);
	vert2 = WFloat3(x2, y2, z2);
	vert3 = WFloat3(x3, y3, z3);
	color = 0x000000;
}

Triangle::Triangle(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	unsigned int _color)
{
	vert1 = WFloat3(x1, y1, z1);
	vert2 = WFloat3(x2, y2, z2);
	vert3 = WFloat3(x3, y3, z3);
	color = _color;
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(float x, float y)
{
	float i1 = (x - vert2.x) * (vert1.y - vert2.y) - (vert1.x - vert2.x) * (y - vert2.y);
	float i2 = (x - vert3.x) * (vert2.y - vert3.y) - (vert2.x - vert3.x) * (y - vert3.y);
	float i3 = (x - vert1.x) * (vert3.y - vert1.y) - (vert3.x - vert1.x) * (y - vert1.y);

	if (i1 > 0 && i2 > 0 && i3 > 0) {
		return true;
	}
	return false;
}