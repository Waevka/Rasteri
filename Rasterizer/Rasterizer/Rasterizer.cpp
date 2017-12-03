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
	Triangle triangle1(	{ 0.0f, 0.0f, 1.0f },
						{ 1.0f, 0.0f, 0.5f }, 
						{ 0.5f, 1.0f, 0.0f },
						0x441100, 0x991100, 0xEE1100);
	Triangle triangle2(	{ 0.0f, 0.0f, 0.0f },
						{ 0.5f, 0.2f, 0.5f },
						{ 0.3f, 0.8f, 1.0f },
						0x004411, 0x009911, 0x00EE11);

	triangles.push_back(triangle1);
	triangles.push_back(triangle2);

	for (int i = 0; i < (int)triangles.size(); i++) {
		Triangle trngl = triangles[i];

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
				HitInfo hitInfo = trngl.intersect(stepx * x, stepy * y);
				if (hitInfo.hasHit) {

					float depth = (trngl.vert1.z * hitInfo.area.x)
						+ (trngl.vert2.z * hitInfo.area.y)
						+ (trngl.vert3.z * hitInfo.area.z);
					//interpolate the color between vertices
					WColor color = (trngl.color1 * hitInfo.area.x)
						+ (trngl.color2 * hitInfo.area.y)
						+ (trngl.color3 * hitInfo.area.z);

					if (i == 0 || depth < buffer.depth[(int)(buffer.width * y + x)]) {
						buffer.writeColor(x, y, color, depth);
					}

				}
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
