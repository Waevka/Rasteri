#pragma once

struct WFloat4x4;

union WFloat4 {
	__m128 m;
	struct
	{
	public:
		float x, y, z, w;
	};

	WFloat4();
	WFloat4(__m128 x);
	WFloat4(float _x, float _y, float _z);
	WFloat4(float _x, float _y, float _z, float _w);
	WFloat4(WFloat4 u, WFloat4 v);
	WFloat4 operator*=(WFloat4x4 matrix);
	WFloat4 operator*(float f);
	WFloat4 operator*(WFloat4 f);
	//WFloat4 operator+(WFloat4 f);
	WFloat4 operator/=(float f);
	WFloat4 normalize();
	float invSqrt(float n);
	float len();
	float len2();
	float getsum();
	static WFloat4 crossProduct(WFloat4 u, WFloat4 v);
	static float dotProduct(WFloat4 u, WFloat4 v);
	~WFloat4();
};
