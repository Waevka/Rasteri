// Rasterizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rasterizer.h"

int main(int argc, char *argv[])
{	
	srand(time(NULL));
	Rasterizer rasterizer(256, 256);
	rasterizer.renderScanline();
    return 0;
}

