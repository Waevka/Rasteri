#pragma once

class WFloat4x4;

class WFloat4
{
public:
	float x, y, z, w;
	WFloat4();
	WFloat4(float _x, float _y, float _z);
	WFloat4(float _x, float _y, float _z, float _w);
	WFloat4(WFloat4 u, WFloat4 v);
	WFloat4 operator*=(WFloat4x4 matrix);
	WFloat4 operator*(float f);
	WFloat4 operator*(WFloat4 f);
	WFloat4 operator+(WFloat4 f);
	WFloat4 operator/=(float f);
	WFloat4 normalize();
	float invSqrt(float n);
	float len();
	float len2();
	static WFloat4 crossProduct(WFloat4 u, WFloat4 v);
	static float dotProduct(WFloat4 u, WFloat4 v);
	~WFloat4();
};

