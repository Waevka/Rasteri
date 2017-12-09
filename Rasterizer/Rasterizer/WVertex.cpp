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
	return *this;
}

WVertex WVertex::operator*=(WFloat4x4 matrix)
{
	pos *= matrix;
	return *this;
}
