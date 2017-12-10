#include "stdafx.h"
#include "WVertex.h"


WVertex::WVertex()
{
	pos = WFloat4(0.0f, 0.0f, 0.0f, 0.0f);
}


WVertex::WVertex(float _x, float _y, float _z)
{
	pos = WFloat4(_x, _y, _z, 1.0f);
}

WVertex::~WVertex()
{
}

WVertex WVertex::operator/=(float f)
{
	pos /= f;
	normal /= f;
	return *this;
}

WVertex WVertex::transform(WFloat4x4 matrix, WFloat4x4 mtrans)
{
	pos *= matrix;
	pos /= pos.w;

	normal *= mtrans;
	normal /= normal.w;

	return *this;
}
