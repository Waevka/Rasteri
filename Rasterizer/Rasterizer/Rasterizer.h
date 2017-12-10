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
	VertexProcessor vertexProcessor;
	FragmentProcessor fragmentProcessor;
	Buffer buffer;
	ITgaSavable *tgaBuffer;
	std::vector<Triangle> triangles;
};

