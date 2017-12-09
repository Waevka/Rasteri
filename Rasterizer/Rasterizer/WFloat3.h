#pragma once
class WFloat4x4;

class WFloat3
{
public:
	float x, y, z;
	WFloat3();
	WFloat3(float _x, float _y, float _z);
	~WFloat3();

	WFloat3 operator*=(WFloat4x4 matrix);

	WFloat3 normalize();
	float len();
};

