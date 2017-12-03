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
	unsigned int r = (this->value >> 16 & 255) * f;
	unsigned int g = (this->value >> 8 & 255) * f;
	unsigned int b = (this->value & 255) * f;
	unsigned int a = (this->value >> 24 & 255) * f;

	return { (a << 24) + (r << 16) + (g << 8) + b };
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
