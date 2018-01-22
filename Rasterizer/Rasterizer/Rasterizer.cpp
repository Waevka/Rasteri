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

float Rasterizer::renderScanline()
{
	//Set up camera
	WFloat4 up(0.0f, 1.0f, 0.0f);
	WFloat4 eye(-1.5f, 2.5f, -3.0f);
	WFloat4 target(0.5f, 0.0f, 0.5f);
	vertexProcessor.lookAt(up, eye, target);
	vertexProcessor.setPerspective(45.0f, BWIDTH * 1.0f / BHEIGHT, 0.2f, 10.0f);

	std::vector<ObjMesh*> meshes;
	std::vector<Light*> lights;

	//Load meshes from files
	ObjMesh *mesh = new ObjMesh("torus.obj");
	ObjMesh *mesh2 = new ObjMesh("ico.obj"); 
	ObjMesh *mesh3 = new ObjMesh("monkey.obj");
	//ObjMesh mesh4("ico.obj");
	//ObjMesh mesh5("ico.obj");
	//ObjMesh mesh6("ico.obj");
	//ObjMesh mesh7("ico.obj");

	meshes.push_back(mesh);
	meshes.push_back(mesh2);
	meshes.push_back(mesh3);
	//meshes.push_back(mesh4);
	//meshes.push_back(mesh5);
	//meshes.push_back(mesh6);
	//meshes.push_back(mesh7);

	//Translate/rotate/scale objects
	meshes[1]->Tv = { 0.0f, 0.0f, 1.0f };
	meshes[2]->Tv = { 0.0f, 0.0f, -1.0f };
	meshes[2]->Rv = { 0.0f, 180.0f, 0.0f};
	//meshes[3].Rv = { 0.0f, 0.0f, 0.0f };
	//meshes[3].Sv = { 1.5f, 1.4f, 1.4f };
	//meshes[3].Tv = { 0.0f, 0.0f, 0.0f };
	//meshes[4].Tv = { 0.0f, 0.0f, 0.0f };
	//meshes[5].Tv = { 0.0f, 0.0f, 0.0f };
	//meshes[6].Tv = { 0.0f, 0.0f, 0.0f };

	//White light
	Light* light = new Light(	{1.0f, 0.0f, 0.0f, 0.0f},
								{0.0f, 0.0f, 0.0f});
	light->setDiffuse(0xFFFFFF);
	light->setSpecular(0x040404);
	light->setAmbient(0x000000);

	lights.push_back(light);
	
	//Red light
	/*Light* light2 = new Light({ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f });

	light2->diffuse = 0xFF0000;
	light2->specular = 0x000000;
	light2->ambient = 0x000000;

	lights.push_back(light2);*/

	//Time
	std::clock_t start;
	double duration;

	start = std::clock();

	for (int i = 0; i < meshes.size(); i++) {
		vertexProcessor.processTransformations(meshes[i], OX, OY, OZ, lights);

		fragmentProcessor.lights = lights;
		for (int j = 0; j < (int)meshes[i]->triangles.size(); j++) {
			fragmentProcessor.trngl = meshes[i]->triangles[j];
			fragmentProcessor.processTriangle(buffer);
		}
	}

	duration = std::clock() - start;
	duration /= (double)CLOCKS_PER_SEC;

	bool success = tgaBuffer->writeToFile(buffer);
	if (!success) {
		std::cout << "FAIL: There was a problem while saving to tga file. :(";
	}
	else {
		std::cout << "Finished saving to render.tga and renderDepth.tga files.";
	}

	std::cout << "\nDuration: " << duration << "s ";
	return duration;

}
