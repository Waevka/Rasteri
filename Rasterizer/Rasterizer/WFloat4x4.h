#pragma once
class WFloat4x4
{
public:
	float matrix[4][4];
	WFloat4x4();
	WFloat4x4(WFloat4 a, WFloat4 b, WFloat4 c, WFloat4 d);
	static WFloat4x4 translate(WFloat4 v);
	static WFloat4x4 scale(WFloat4 v);
	static WFloat4x4 rotate(float a, WFloat4 v);
	static WFloat4x4 identity();
	static WFloat4x4 lookAt(WFloat4 up, WFloat4 eye, WFloat4 target);
	static WFloat4x4 perspective(float fov, float ratio, float near, float far);

	WFloat4x4 operator*(WFloat4x4 N);

 	~WFloat4x4();
};

