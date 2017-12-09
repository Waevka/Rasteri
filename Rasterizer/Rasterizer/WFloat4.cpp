#include "stdafx.h"
#include "WFloat4.h"


WFloat4::WFloat4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}


WFloat4::WFloat4(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	w = 1.0f;
}

WFloat4::WFloat4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

WFloat4::WFloat4(WFloat4 u, WFloat4 v)
{
	x = v.x - u.x;
	y = v.y - u.y;
	z = v.z - u.z;
	w = 1.0f;
}

WFloat4 WFloat4::operator*=(WFloat4x4 matrix)
{
	WFloat4 u(*this);
	x = (matrix.matrix[0][0] * u.x) + (matrix.matrix[0][1] * u.y) + (matrix.matrix[0][2] * u.z) + (matrix.matrix[0][3] * u.w);
	y = (matrix.matrix[1][0] * u.x) + (matrix.matrix[1][1] * u.y) + (matrix.matrix[1][2] * u.z) + (matrix.matrix[1][3] * u.w);
	z = (matrix.matrix[2][0] * u.x) + (matrix.matrix[2][1] * u.y) + (matrix.matrix[2][2] * u.z) + (matrix.matrix[2][3] * u.w);
	w = (matrix.matrix[3][0] * u.x) + (matrix.matrix[3][1] * u.y) + (matrix.matrix[3][2] * u.z) + (matrix.matrix[3][3] * u.w);

	return *this;
}

WFloat4 WFloat4::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
}

WFloat4 WFloat4::normalize()
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

float WFloat4::len()
{
	return std::sqrt(x * x + y * y + z * z);
}

WFloat4 WFloat4::crossProduct(WFloat4 u, WFloat4 v)
{
	return WFloat4((u.y*v.z) - (u.z*v.y),
		(u.z*v.x) - (u.x*v.z),
		(u.x*v.y) - (u.y*v.x));
}

float WFloat4::dotProduct(WFloat4 u, WFloat4 v)
{
	return (u.x*v.x) + (u.y*v.y) + (u.z*v.z);
}

WFloat4::~WFloat4()
{
}

