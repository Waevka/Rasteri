#pragma once
class WFloat4x4
{
public:
	float matrix[4][4];
	WFloat4x4();
	WFloat4x4(WFloat4 a, WFloat4 b, WFloat4 c, WFloat4 d);
	static WFloat4x4 identity();
	WFloat4x4 transpose();
	WFloat4x4 operator*(WFloat4x4 N);

 	~WFloat4x4();
};

