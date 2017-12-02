#include "stdafx.h"
#include "Rasterizer.h"


Rasterizer::Rasterizer()
{
	tgaBuffer = new TgaBuffer();
}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::renderScanline()
{
	bool success = tgaBuffer->save(buffer);
	if (!success) {
		std::cout << "There was a problem while saving to tga file.";
	}
	else {
		std::cout << "Finished saving to render.tga file.";
	}
}
