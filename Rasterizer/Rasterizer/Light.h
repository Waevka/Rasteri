#pragma once
struct Light
{
private:
	WColor ambient;
	WColor specular;
	WColor diffuse;
public:
	WFloat4 o;
	WFloat4 d;
	Light(WFloat4 _o, WFloat4 _d);
	~Light();
	__m128 getDirection(WFloat4 dir);

	Light operator*=(WFloat4x4 matrix);
	Light operator/=(float f);
	void setDiffuse(unsigned int c);
	void setSpecular(unsigned int c);
	void setAmbient(unsigned int c);
	WColor getDiffuse();
	WColor getSpecular();
	WColor getAmbient();
};

