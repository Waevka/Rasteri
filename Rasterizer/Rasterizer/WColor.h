#pragma once
class WColor
{
public:
	unsigned int value;
	WColor();
	WColor(unsigned int c);
	~WColor();
	WColor operator+(WColor color2);
	WColor operator+(float f);
	WColor operator*(float f);
	WColor operator=(WColor color2);
	WColor operator=(unsigned int col);
};

