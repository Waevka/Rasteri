#include "stdafx.h"
#include "Light.h"

inline __m128 CrossProduct(__m128 u, __m128 v) {
	return _mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(u, u, _MM_SHUFFLE(3, 0, 2, 1)),
			_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 0, 2))),
		_mm_mul_ps(
			_mm_shuffle_ps(u, u, _MM_SHUFFLE(3, 1, 0, 2)),
			_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1)))
	);
}

Light::Light(WFloat4 _o, WFloat4 _d)
{
	o = _o;
	d = _d;
	ambient = 0xAAAAAA;
	diffuse = 0xEEEEEE;
	specular = 0xFFFFFF;
}

Light::~Light()
{
}

__m128 Light::getDirection(WFloat4 dir)
{
	if (o.w == 0.0f) {
		return d.m;
	}
	else if (o.w == 1.0f) {
		return CrossProduct(dir.m, o.m); //WFloat4(dir, o);
	}
}

Light Light::operator*=(WFloat4x4 matrix)
{
	o *= matrix;
	o /= o.w;

	d *= matrix;
	d /= d.w;

	return *this;
}

Light Light::operator/=(float f)
{
	o /= f;
	d /= f;
	return *this;
}

void Light::setDiffuse(unsigned int c)
{
	this->diffuse = c;
}

void Light::setSpecular(unsigned int c)
{
	this->specular = c;
}

void Light::setAmbient(unsigned int c)
{
	this->ambient = c;
}

WColor Light::getDiffuse()
{
	return this->diffuse;
}

WColor Light::getSpecular()
{
	return specular;
}

WColor Light::getAmbient()
{
	return ambient;
}
