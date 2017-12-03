#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle()
{
	vert1 = WFloat3(0.0f, 0.0f, 0.0f);
	vert2 = WFloat3(2.0f, 0.0f, 0.0f);
	vert3 = WFloat3(1.0f, 1.0f, 0.0f);
	color1 = color2 = color3 = 0x000000;
}

Triangle::Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
	color1 = color2 = color3 = 0x000000;
}

Triangle::Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, WColor _color)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
	color1 = color2 = color3 = _color;
}

Triangle::Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, WColor _color1, WColor _color2, WColor _color3)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
	color1 = _color1;
	color2 = _color2;
	color3 = _color3;
}

Triangle::~Triangle()
{
}

HitInfo Triangle::intersect(float x, float y)
{	
	HitInfo hitInfo;

	float AB = (x - vert2.x) * (vert1.y - vert2.y) - (vert1.x - vert2.x) * (y - vert2.y);
	float BC = (x - vert3.x) * (vert2.y - vert3.y) - (vert2.x - vert3.x) * (y - vert3.y);
	float CA = (x - vert1.x) * (vert3.y - vert1.y) - (vert3.x - vert1.x) * (y - vert1.y);

	if (AB > 0 && BC > 0 && CA > 0) {
		hitInfo.hasHit = true;
		float area = 1.0f / ((vert3.x - vert1.x) * (vert2.y - vert1.y) - (vert2.x - vert1.x) * (vert3.y - vert1.y));
		hitInfo.area.x = BC * area;
		hitInfo.area.y = CA * area;
		hitInfo.area.z = AB * area;
	}

	return hitInfo;
}
