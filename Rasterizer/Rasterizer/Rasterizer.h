#pragma once
class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();
	void renderScanline();
private:
	Buffer buffer;
	ITgaSavable *tgaBuffer;
	std::list<Model> models;
};

