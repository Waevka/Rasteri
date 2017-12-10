#include "stdafx.h"
#include "WColor.h"


WColor::WColor()
{
	value = 0xAAAAAA;
}

WColor::WColor(unsigned int c)
{
	this->value = c;
}


WColor::~WColor()
{
}

WColor WColor::operator+(WColor color2)
{
	this->value += color2.value;
	return *this;
}

WColor WColor::operator+(float f)
{
	this->value += f;
	return *this;
}

WColor WColor::operator*(float f)
{
	unsigned int r = getR() * f;
	unsigned int g = getG() * f;
	unsigned int b = getB() * f;
	unsigned int a = getA() * f;

	return { (a << 24) + (r << 16) + (g << 8) + b };
}

WColor WColor::operator*(WFloat4 f)
{
	unsigned int a = f.w * getA();
	unsigned int r = f.x * getR();
	unsigned int g = f.y * getG();
	unsigned int b = f.z * getB();

	return { (a << 24) + (r << 16) + (g << 8) + (b) };

}

WColor WColor::operator*(WColor c)
{
	float div = 1.0f / 255;

	float a = c.getA()*div * getA();
	float r = c.getR()*div * getR();
	float g = c.getG()*div * getG();
	float b = c.getB()*div * getB();

	return { ((unsigned int)a << 24)
		+ ((unsigned int)r << 16)
		+ ((unsigned int)g << 8)
		+ ((unsigned int)b) };
}

WColor WColor::operator=(WColor color2)
{
	this->value = color2.value;
	return *this;
}

WColor WColor::operator=(unsigned int col)
{
	this->value = col;
	return *this;
}

unsigned int WColor::getR()
{
	return (value >> 16 & 255);
}

unsigned int WColor::getG()
{
	return (value >> 8 & 255);
}

unsigned int WColor::getB()
{
	return (value & 255);
}

unsigned int WColor::getA()
{
	return (value >> 24 & 255);
}
