#pragma once
class WVertex
{
public:
	WFloat4 pos;
	WFloat4 normal;
	WFloat4 uv;
	WColor color;
	WVertex();
	WVertex(float _x, float _y, float _z);
	~WVertex();
	WVertex operator /= (float f);
	WVertex transform(WFloat4x4 matrix, WFloat4x4 mtrans);
};

