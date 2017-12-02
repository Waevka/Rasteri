#pragma once
#include "ITgaSavable.h"
class TgaBuffer :
	public ITgaSavable
{
public:
	TgaBuffer();
	~TgaBuffer();
	bool save(Buffer buffer);
};

