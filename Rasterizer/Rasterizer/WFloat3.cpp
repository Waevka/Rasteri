#include "stdafx.h"
#include "WFloat3.h"


WFloat3::WFloat3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

WFloat3::WFloat3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}


WFloat3::~WFloat3()
{
}

WFloat3 WFloat3::operator*=(WFloat4x4 matrix)
{
	float xt = x;
	float yt = y;
	float zt = z;
	x = (matrix.matrix[0][0] * xt) + (matrix.matrix[0][1] * yt) + (matrix.matrix[0][2] * zt) + (matrix.matrix[0][3]);
	y = (matrix.matrix[1][0] * xt) + (matrix.matrix[1][1] * yt) + (matrix.matrix[1][2] * zt) + (matrix.matrix[1][3]);
	z = (matrix.matrix[2][0] * xt) + (matrix.matrix[2][1] * yt) + (matrix.matrix[2][2] * zt) + (matrix.matrix[2][3]);
	return *this;
}

WFloat3 WFloat3::normalize()
{
	float length = len();
	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}

float WFloat3::len()
{
	return std::sqrt(x * x + y * y + z * z);
}
