// Rasterizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rasterizer.h"

int main(int argc, char *argv[])
{	
	srand(time(NULL));
	float avg = 0;
	for (int i = 0; i < 10; i++) {
		Rasterizer rasterizer(1024, 1024);
		avg += rasterizer.renderScanline();
	}
	avg /= 10.0f;
	std::cout << "\n\nAvg time from 100 renders: " << avg;
	std::cin.get();
    return 0;
}

