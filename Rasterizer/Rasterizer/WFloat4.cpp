#include "stdafx.h"
#include "WFloat4.h"


WFloat4::WFloat4() : m(_mm_setzero_ps())
{
	//x = 0.0f;
	//y = 0.0f;
	//z = 0.0f;
	//w = 1.0f;
}

WFloat4::WFloat4(__m128 _m) : m(_m)
{
	//this->m = m;
}


WFloat4::WFloat4(float _x, float _y, float _z) : m(_mm_set_ps(1.0f, _z, _y, _x))
{
	//x = _x;
	//y = _y;
	//z = _z;
	//w = 1.0f;
}

WFloat4::WFloat4(float _x, float _y, float _z, float _w) : m(_mm_set_ps(_w, _z, _y, _x))
{
	//x = _x;
	//y = _y;
	//z = _z;
	//w = _w;
}

WFloat4::WFloat4(WFloat4 u, WFloat4 v)
{
	m = _mm_sub_ps(v.m, u.m);
	//x = v.x - u.x;
	//y = v.y - u.y;
	//z = v.z - u.z;
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

WFloat4 WFloat4::operator*(float f)
{
	//WFloat4 r(*this);
	//r.y *= f;
	//r.z *= f;
	//r.x *= f;
	//r.w *= f;

	//return WFloat4(x *f, y *f, z*f, w*f);
	return WFloat4(_mm_mul_ps(m, _mm_set1_ps(f)));
}

WFloat4 WFloat4::operator*(WFloat4 f)
{
	//WFloat4 r(*this);
	//r.y *= f.y;
	//r.z *= f.z;
	//r.x *= f.x;
	//r.w *= f.w;
	//return WFloat4(x * f.x, y *f.y, z*f.z, w*f.w);
	return WFloat4(_mm_mul_ps(m, f.m));
	//return r;
}

__m128 WFloat4::operator+(__m128 f)
{
	return _mm_add_ps(m, f);
}

WFloat4 WFloat4::operator+(WFloat4 f)
{
	//WFloat4 r(*this);
	//r.y += f.y;
	//r.z += f.z;
	//r.x += f.x;
	//r.w += f.w;

	//return r;
	return WFloat4(_mm_add_ps(m, f.m));
}

WFloat4 WFloat4::operator/=(float f)
{
	if (f == 0) {
		f = 1.0f / 0.0001f;
	}
	else {
		f = 1.0f / f;
	}

	m = _mm_mul_ps(m, _mm_set1_ps(f));
	//y *= f;
	//z *= f;
	//x *= f;
	//w *= f;

	return *this;
}

WFloat4 WFloat4::normalize()
{
	float length = len2();
	float mag = Magnitude();
	if (mag >= 0.001f) {
		(*this) /= mag;
	}/*
	if (length != 0)
	{	
		length = invSqrt(length);
		x *= length;
		y *= length;
		z *= length;
		//m = _mm_mul_ps(m, _mm_set1_ps(length));
		m = _mm_div_ps(m, _mm_sqrt_ps(_mm_dp_ps(m, m, 0x7F)));
	}*/
	return *this;
}

void WFloat4::normalizeSSE()
{
	float length = len2();
	if (length != 0)
	{
		//length = invSqrt(length);
		//x *= length;
		//y *= length;
		//z *= length;
		m = _mm_mul_ps(m, _mm_rsqrt_ps(_mm_dp_ps(m, m, 0x77)));
	}
}

float WFloat4::invSqrt(float n)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	//Hello Doom
	x2 = n * 0.5F;
	y = n;
	i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));
	return y;
}

float WFloat4::Magnitude() {
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m, m, 0x71)));
}

float WFloat4::len()
{
	return std::sqrt(x * x + y * y + z * z);
}

float WFloat4::len2()
{
	return (x*x) + (y*y) + (z*z);
}

WFloat4 WFloat4::crossProduct(WFloat4& u, WFloat4& v)
{
	return WFloat4((u.y*v.z) - (u.z*v.y),
		(u.z*v.x) - (u.x*v.z),
		(u.x*v.y) - (u.y*v.x));
}

float WFloat4::dotProduct(WFloat4 u, WFloat4 v)
{
	return (u.x*v.x) + (u.y*v.y) + (u.z*v.z);
}

float WFloat4::dotProductSSE(WFloat4 & rhs)
{
	return _mm_cvtss_f32(_mm_dp_ps(m, rhs.m, 0x71));
}

WFloat4::~WFloat4()
{
}

