#include "stdafx.h"
#include "WFloat4x4.h"



WFloat4x4::WFloat4x4()
{
}

WFloat4x4::WFloat4x4(WFloat4 a, WFloat4 b, WFloat4 c, WFloat4 d)
{
	matrix[0][0] = a.x; matrix[0][1] = a.y; matrix[0][2] = a.z; matrix[0][3] = a.w;
	matrix[1][0] = b.x; matrix[1][1] = b.y; matrix[1][2] = b.z; matrix[1][3] = b.w;
	matrix[2][0] = c.x; matrix[2][1] = c.y; matrix[2][2] = c.z; matrix[2][3] = c.w;
	matrix[3][0] = d.x; matrix[3][1] = d.y; matrix[3][2] = d.z; matrix[3][3] = d.w;
}

WFloat4x4 WFloat4x4::translate(WFloat4 v)
{
	WFloat4x4 T = { {1.0f, 0, 0, v.x},
					{0, 1.0f, 0, v.y},
					{0, 0, 1, v.z},
					{0, 0, 0, 1} };
	return T;
}

WFloat4x4 WFloat4x4::scale(WFloat4 v)
{
	WFloat4x4 S = { {v.x, 0.0f, 0.0f, 0.0f},
					{0.0f, v.y, 0.0f, 0.0f},
					{0.0f, 0.0f, v.z, 0.0f},
					{0.0f, 0.0f, 0.0f, 1.0f} };
	return S;
}

WFloat4x4 WFloat4x4::rotate(float a, WFloat4 v)
{
	float rad = (float)(M_PI / 180.0f);
	float s = std::sin(a * rad);
	float c = std::cos(a * rad);

	v = v.normalize();
	WFloat4x4 R = { { v.x*v.x*(1 - c) + c, v.x*v.y*(1 - c) - v.z*s, v.x*v.z*(1 - c) + v.y*s, 0 },
					{ v.x*v.y*(1 - c) + v.z*s,  v.y*v.y*(1 - c) + c   , v.z*v.y*(1 - c) - v.x*s, 0 },
					{ v.x*v.z*(1 - c) - v.y*s, v.z*v.y*(1 - c) + v.x*s, v.z*v.z*(1 - c) + c    , 0 },
					{ 0, 0, 0, 1 } };

	return R;
}

WFloat4x4 WFloat4x4::identity()
{
	return WFloat4x4({1.0f, 0, 0, 0}, 
					{0, 1.0f, 0, 0},
					{0, 0, 1.0f, 0},
					{0, 0, 0, 1.0f});
}

WFloat4x4 WFloat4x4::lookAt(WFloat4 up, WFloat4 eye, WFloat4 target)
{
	up = up.normalize();
	WFloat4 forward = WFloat4(eye, target).normalize();
	WFloat4 right = WFloat4::crossProduct(up, forward).normalize();
	up = WFloat4::crossProduct(forward, right);

	WFloat4x4 Mov = { { 1, 0, 0, -eye.x },
	{ 0, 1, 0, -eye.y },
	{ 0, 0, 1, -eye.z },
	{ 0, 0, 0, 1 } };

	WFloat4x4 Rot = {	{ right.x,    right.y,    right.z,    0 },
						{ up.x,       up.y,       up.z,       0 },
						{ forward.x, forward.y, forward.z,    0 },
						{ 0,          0,          0,          1 } };
	return Rot * Mov;
}

WFloat4x4 WFloat4x4::perspective(float fov, float ratio, float near, float far)
{

	float f_n = 1.0f / (far - near);
	fov *= (float)(M_PI / 360);
	float f = std::cos(fov) / std::sin(fov);
	ratio = 1.0f / ratio;

	WFloat4x4 M = { { f*ratio,   0,        0,               0 },
					{ 0,         f,        0,               0 },
					{ 0,         0,        (far + near)*f_n,  -(2 * far*near)*f_n },
					{ 0,         0,        1,              1 } };

	return M;
}

WFloat4x4 WFloat4x4::operator*(WFloat4x4 N)
{

	WFloat4x4 M = { { 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 } };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				M.matrix[i][j] += matrix[i][k] * N.matrix[k][j];
			}
		}
	}

	return M;
}

WFloat4x4::~WFloat4x4()
{
}
