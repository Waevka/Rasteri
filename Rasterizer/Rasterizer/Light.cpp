#include "stdafx.h"
#include "Light.h"


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

WFloat4 Light::getVector(WFloat4 dir)
{
	if (o.w == 0.0f) {
		return d;
	}
	else if (o.w == 1.0f) {
		return WFloat4(dir, o);
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
