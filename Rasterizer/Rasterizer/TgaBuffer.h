#pragma once
#include "ITgaSavable.h"
class TgaBuffer :
	public ITgaSavable
{
public:
	TgaBuffer();
	TgaBuffer(int w, int h);
	~TgaBuffer();
	bool save(Buffer buffer);
};

