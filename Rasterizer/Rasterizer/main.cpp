// Rasterizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rasterizer.h"

int main(int argc, char *argv[])
{	
	Rasterizer rasterizer(256, 256);
	rasterizer.renderScanline();
    return 0;
}

