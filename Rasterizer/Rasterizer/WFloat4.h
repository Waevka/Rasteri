#pragma once

class WFloat4x4;

__declspec(align(32)) class WFloat4
{
public:
	__declspec(align(32)) union {
		__m128 m;
		struct { float x, y, z, w; };
	};
	WFloat4();
	WFloat4(__m128 m);
	WFloat4(float _x, float _y, float _z);
	WFloat4(float _x, float _y, float _z, float _w);
	WFloat4(WFloat4 u, WFloat4 v);
	WFloat4 operator*=(WFloat4x4 matrix);
	WFloat4 operator*(float f);
	WFloat4 operator*(WFloat4 f);
	__m128 operator+(__m128 f);
	WFloat4 operator+(WFloat4 f);
	WFloat4 operator/=(float f);
	WFloat4 normalize();
	void normalizeSSE();
	float invSqrt(float n);
	float len();
	float len2();
	static WFloat4 crossProduct(WFloat4& u, WFloat4& v);
	static float dotProduct(WFloat4 u, WFloat4 v);
	float dotProductSSE(WFloat4 &rhs);
	~WFloat4();
};

