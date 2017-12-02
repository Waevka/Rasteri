#pragma once
class Buffer
{
public:
	Buffer();
	~Buffer();
	ITgaSavable *TgaBuffer;
	void setSize(int size);
};

