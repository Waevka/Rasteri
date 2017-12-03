#pragma once
#include "Model.h"
class Triangle :
	public Model
{
public:
	WFloat3 vert1, vert2, vert3;
	unsigned int color = 0;
	Triangle();
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3);
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, unsigned int _color);
	Triangle(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3);
	Triangle(
			float x1, float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			unsigned int _color);
	~Triangle();
	HitInfo intersect(float x, float y);
};

