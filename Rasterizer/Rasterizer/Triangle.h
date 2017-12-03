#pragma once
#include "Model.h"
class Triangle :
	public Model
{
public:
	WFloat3 vert1, vert2, vert3;
	WColor color1;
	WColor color2;
	WColor color3;
	Triangle();
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3);
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, WColor _color);
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3,
		WColor _color1, WColor _color2, WColor _color3);
	~Triangle();
	HitInfo intersect(float x, float y);
};

