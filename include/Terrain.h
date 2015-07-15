#pragma once
#include <stdint.h>

class Terrain
{
public:
	Terrain();
	~Terrain();

private:
	static const uint32_t WIDTH = 10;
	static const uint32_t HEIGHT = 10;
	uint16_t Tiles[WIDTH][HEIGHT];
	
};

