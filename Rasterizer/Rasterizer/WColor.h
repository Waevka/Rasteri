#pragma once
struct WColor
{
public:
	unsigned int value;
	WColor();
	WColor(unsigned int c);
	~WColor();
	WColor operator+(WColor color2);
	WColor operator+(float f);
	WColor operator*(float f);
	WColor operator*(WFloat4 f);
	WColor operator*(WColor c);
	WColor operator=(WColor color2);
	WColor operator=(unsigned int col);
	WColor &operator +=(const WColor &col2);
	unsigned inline int getR();
	unsigned inline int getG();
	unsigned inline int getB();
	unsigned inline int getA();
};

