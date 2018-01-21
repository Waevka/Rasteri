#pragma once
class WFloat4x4;

__declspec(align(32)) class WFloat3
{
public:
	__declspec(align(32)) union {
		struct { float x, y, z; };
		__m128 mmv;
	};
	WFloat3();
	WFloat3(float _x, float _y, float _z);
	~WFloat3();

	WFloat3 operator*=(WFloat4x4 matrix);

	WFloat3 normalize();
	float len();
};

