#pragma once
class Rasterizer
{
public:
	Rasterizer();
	Rasterizer(int w, int h);
	~Rasterizer();
	void renderScanline();
private:
	Buffer buffer;
	ITgaSavable *tgaBuffer;
	std::list<Model> models;
};

