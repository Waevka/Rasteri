#include "stdafx.h"
#include "Rasterizer.h"


Rasterizer::Rasterizer()
{
	tgaBuffer = new TgaBuffer();
	OX = { 1.0f, 0.0f, 0.0f };
	OY = { 0.0f, 1.0f, 0.0f };
	OZ = { 0.0f, 0.0f, 1.0f };
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
	ObjMesh mesh("torus.obj");
	ObjMesh mesh2("ico.obj");
	/*
	WFloat4 Tv = { 0.0f, 0.0f, 0.0f };
	WFloat4 Rv = { 0.0f, 0.0f, 0.0f };
	WFloat4 Sv = { 1.0f, 1.0f, 1.0f };
	
	WFloat4 ox = { 1.0f, 0.0f, 0.0f };
	WFloat4 oy = { 0.0f, 1.0f, 0.0f };
	WFloat4 oz = { 0.0f, 0.0f, 1.0f };

	WFloat4x4 T = WFloat4x4::translate(Tv);
	WFloat4x4 Rx = WFloat4x4::rotate(Rv.x, ox);
	WFloat4x4 Ry = WFloat4x4::rotate(Rv.y, oy);
	WFloat4x4 Rz = WFloat4x4::rotate(Rv.z, oz);
	WFloat4x4 R = Rz * Ry * Rx;
	WFloat4x4 S = WFloat4x4::scale(Sv);

	WFloat4x4 M = T * S * R;
	*/

	std::vector<ObjMesh> meshes;
	meshes.push_back(mesh);
	meshes.push_back(mesh2);
	meshes[1].Tv = {-0.5f, -0.0f, 1.0f};

	WFloat4 up(0.0f, 1.0f, 0.0f);
	WFloat4 eye(-1.5f, 2.5f, -3.0f);
	WFloat4 target(0.5f, 0.0f, 0.5f);

	WFloat4x4 V = WFloat4x4::lookAt(up, eye, target);
	WFloat4x4 P = WFloat4x4::perspective(45.0f, buffer.width*1.0f / buffer.height, 0.5, 3);

	//WFloat4x4 MVP = P * V * M;

	for (int i = 0; i < meshes.size(); i++) {

		WFloat4x4 T = WFloat4x4::translate(meshes[i].Tv);
		WFloat4x4 Rx = WFloat4x4::rotate(meshes[i].Rv.x, OX);
		WFloat4x4 Ry = WFloat4x4::rotate(meshes[i].Rv.y, OY);
		WFloat4x4 Rz = WFloat4x4::rotate(meshes[i].Rv.z, OZ);

		WFloat4x4 R = Rz * Ry * Rx;
		WFloat4x4 S = WFloat4x4::scale(meshes[i].Sv);

		WFloat4x4 M = T * S *R;
		WFloat4x4 MVP = P * V * M;

		for (int j = 0; j < meshes[i].vertices.size(); j++) {

			std::cout << "Before: " << meshes[i].vertices[j]->pos.x << " "
				<< meshes[i].vertices[j]->pos.y << " "
				<< meshes[i].vertices[j]->pos.z << " "
				<< meshes[i].vertices[j]->pos.w << std::endl;

			meshes[i].vertices[j]->operator*=(MVP);
			meshes[i].vertices[j]->operator/=(meshes[i].vertices[j]->pos.w);

			std::cout << "After: " << meshes[i].vertices[j]->pos.x << " "
				<< meshes[i].vertices[j]->pos.y << " "
				<< meshes[i].vertices[j]->pos.z << " "
				<< meshes[i].vertices[j]->pos.w << std::endl;
		}

		float stepx = 1.0f / buffer.width;
		float stepy = 1.0f / buffer.height;

		for (int j = 0; j < (int)meshes[i].triangles.size(); j++) {
			Triangle trngl = *(meshes[i].triangles[j]);

			//define minmax values for canvas
			buffer.maxx = (trngl.A->pos.x > trngl.B->pos.x) ? trngl.A->pos.x : trngl.B->pos.x;
			buffer.maxx = (buffer.maxx > trngl.C->pos.x) ? buffer.maxx : trngl.C->pos.x;

			buffer.minx = (trngl.A->pos.x < trngl.B->pos.x) ? trngl.A->pos.x : trngl.B->pos.x;
			buffer.minx = (buffer.minx < trngl.C->pos.x) ? buffer.minx : trngl.C->pos.x;

			buffer.maxy = (trngl.A->pos.y > trngl.B->pos.y) ? trngl.A->pos.y : trngl.B->pos.y;
			buffer.maxy = (buffer.maxy > trngl.C->pos.y) ? buffer.maxy : trngl.C->pos.y;

			buffer.miny = (trngl.A->pos.y < trngl.B->pos.y) ? trngl.A->pos.y : trngl.B->pos.y;
			buffer.miny = (buffer.miny < trngl.C->pos.y) ? buffer.miny : trngl.C->pos.y;

			buffer.maxx>1 ? buffer.maxx = 1 : buffer.maxx<-1 ? buffer.maxx = -1 : true;
			buffer.maxy>1 ? buffer.maxy = 1 : buffer.maxy<-1 ? buffer.maxy = -1 : true;

			buffer.minx>1 ? buffer.minx = 1 : buffer.minx<-1 ? buffer.minx = -1 : true;
			buffer.miny>1 ? buffer.miny = 1 : buffer.miny<-1 ? buffer.miny = -1 : true;

			buffer.maxx = 1.0f; buffer.maxy = 1.0f;
			buffer.minx = -1.0f; buffer.miny = -1.0f;

			//intersection for each pixel
			for (float x = buffer.minx; x <= buffer.maxx; x += stepx) {
				for (float y = buffer.miny; y <= buffer.maxy; y += stepy) {

					HitInfo hitInfo = trngl.intersect(x, y);
					if (hitInfo.hasHit) {

						float depth = (trngl.A->pos.z * hitInfo.area.x)
							+ (trngl.B->pos.z * hitInfo.area.y)
							+ (trngl.C->pos.z * hitInfo.area.z);
						//interpolate the color between vertices
						WColor color = (trngl.A->color * hitInfo.area.x)
							+ (trngl.B->color * hitInfo.area.y)
							+ (trngl.C->color * hitInfo.area.z);

						if (depth >= -1 && depth <= 1) {
							//std::cout << x << " " << y << std::endl;
							int x1 = (x + 1) * buffer.width * 0.5f;
							int y1 = (y + 1) * buffer.height * 0.5f;
							bool test1 = (depth < buffer.depth[(int)(buffer.width * y1 + x1)]);
							bool test2 = (buffer.depth[(int)(buffer.width * y1 + x1)]) == 1;
							if (j == 0 || test1 || test2) {
								buffer.writeColor(x1, y1, color, depth);
							}
						}

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
