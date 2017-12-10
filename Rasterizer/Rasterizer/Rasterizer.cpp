#include "stdafx.h"
#include "Rasterizer.h"


Rasterizer::Rasterizer()
{
	tgaBuffer = new TgaBuffer();
	OX = { 1.0f, 0.0f, 0.0f };
	OY = { 0.0f, 1.0f, 0.0f };
	OZ = { 0.0f, 0.0f, 1.0f };
	vertexProcessor.setIdentity();
}

Rasterizer::Rasterizer(int w, int h)
{
	tgaBuffer = new TgaBuffer();
	OX = { 1.0f, 0.0f, 0.0f };
	OY = { 0.0f, 1.0f, 0.0f };
	OZ = { 0.0f, 0.0f, 1.0f };
	vertexProcessor.setIdentity();
	//buffer.setSize(w, h);
}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::renderScanline()
{	
	ObjMesh mesh("torus.obj");
	ObjMesh mesh2("ico.obj"); 
	ObjMesh mesh3("monkey.obj");

	std::vector<ObjMesh> meshes;
	std::vector<Light*> lights;

	meshes.push_back(mesh);
	meshes.push_back(mesh2);
	meshes.push_back(mesh3);
	meshes[1].Tv = { 0.0f, 0.0f, 1.0f };
	meshes[2].Tv = { 0.0f, 0.0f, -1.0f };
	meshes[2].Rv = { 0.0f, 180.0f, 0.0f};

	Light* light = new Light(	{1.0f, 0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f});
	light->diffuse = 0xFFFFFF;
	light->specular = 0x000000;
	light->ambient = 0x000000;

	lights.push_back(light);

	//Needs color clamping
	//Light* light2 = new Light({ 1.0f, 0.0f, 0.0f, 0.0f },
	//	{ 0.0f, 0.0f, 0.0f });

	//light2->diffuse = 0xFF0000;
	//light2->specular = 0x000000;
	//light2->ambient = 0x000000;

	//lights.push_back(light2);

	WFloat4 up(0.0f, 1.0f, 0.0f);
	WFloat4 eye(-1.5f, 2.5f, -3.0f);
	WFloat4 target(0.5f, 0.0f, 0.5f);

	vertexProcessor.lookAt(up, eye, target);
	vertexProcessor.setPerspective(45.0f, buffer.width * 1.0f / buffer.height, 0.2f, 10.0f);

	for (int i = 0; i < meshes.size(); i++) {

		vertexProcessor.vertexBuffer = meshes[i].vertices;
		vertexProcessor.lightBuffer = lights;

		vertexProcessor.translate(meshes[i].Tv);
		vertexProcessor.rotate(meshes[i].Rv.x, OX);
		vertexProcessor.rotate(meshes[i].Rv.y, OY);
		vertexProcessor.rotate(meshes[i].Rv.z, OZ);
		vertexProcessor.scale(meshes[i].Sv);

		vertexProcessor.transform();

		fragmentProcessor.lights = lights;

		for (int j = 0; j < (int)meshes[i].triangles.size(); j++) {

			fragmentProcessor.trngl = (meshes[i].triangles[j]);
			fragmentProcessor.processTriangle(buffer);
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
