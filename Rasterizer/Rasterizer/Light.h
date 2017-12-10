#pragma once
class Light
{
public:
	WFloat4 o;
	WFloat4 d;
	WColor ambient;
	WColor specular;
	WColor diffuse;
	Light(WFloat4 _o, WFloat4 _d);
	~Light();
	WFloat4 getVector(WFloat4 dir);

	Light operator*=(WFloat4x4 matrix);
	Light operator/=(float f);
};

