#pragma once
class Rasterizer
{
public:
	Rasterizer();
	Rasterizer(int w, int h);
	~Rasterizer();
	void renderScanline();
	WFloat4 OX, OY, OZ;
private:
	Buffer buffer;
	ITgaSavable *tgaBuffer;
	std::list<Model> models;
	std::vector<Triangle> triangles;
};

