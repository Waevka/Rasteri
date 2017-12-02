#include "stdafx.h"
#include "Rasterizer.h"


Rasterizer::Rasterizer()
{
	tgaBuffer = new TgaBuffer();
}

Rasterizer::Rasterizer(int w, int h)
{
	tgaBuffer = new TgaBuffer();
	//buffer.setSize(w, h);
}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::renderScanline()
{	
	float stepx = 1.0f / buffer.width;
	float stepy = 1.0f / buffer.height;

	//define a test triangle
	Triangle trngl(	{0.0f, 0.0f, 0.0f},
					{1.0f, 0.0f, 0.0f}, 
					{0.5f, 1.0f, 0.0f},
					0xFFFFAA);

	//define minmax values for canvas
	buffer.maxx = (trngl.vert1.x > trngl.vert2.x) ? trngl.vert1.x : trngl.vert2.x;
	buffer.maxx = (buffer.maxx > trngl.vert3.x) ? buffer.maxx : trngl.vert3.x;

	buffer.minx = (trngl.vert1.x < trngl.vert2.x) ? trngl.vert1.x : trngl.vert2.x;
	buffer.minx = (buffer.minx < trngl.vert3.x) ? buffer.minx : trngl.vert3.x;

	buffer.maxy = (trngl.vert1.y > trngl.vert2.y) ? trngl.vert1.y : trngl.vert2.y;
	buffer.maxy = (buffer.maxy > trngl.vert3.y) ? buffer.maxy : trngl.vert3.y;

	buffer.miny = (trngl.vert1.y < trngl.vert2.y) ? trngl.vert1.y : trngl.vert2.y;
	buffer.miny = (buffer.miny < trngl.vert3.y) ? buffer.miny : trngl.vert3.y;

	//intersection for each pixel
	for (float x = buffer.minx * buffer.width; x < buffer.maxx * buffer.width; x++) {
		for (float y = buffer.miny * buffer.height; y < buffer.maxy * buffer.height; y++) {
			if (trngl.intersect(stepx * x, stepy * y)) {
				buffer.writeColor(x, y, trngl.color, 1.0f);
			}
		}
	}

	bool success = tgaBuffer->save(buffer);
	if (!success) {
		std::cout << "FAIL: There was a problem while saving to tga file. :(";
	}
	else {
		std::cout << "Finished saving to render.tga file.";
	}
}
