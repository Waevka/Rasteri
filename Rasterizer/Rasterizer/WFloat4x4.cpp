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

WFloat4x4 WFloat4x4::identity()
{
	return WFloat4x4({1.0f, 0, 0, 0}, 
					{0, 1.0f, 0, 0},
					{0, 0, 1.0f, 0},
					{0, 0, 0, 1.0f});
}

WFloat4x4 WFloat4x4::transpose()
{
	WFloat4x4 M = { { matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0] },
					{ matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1] },
					{ matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2] },
					{ matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3] } };
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
