#pragma once
#include <stdint.h>
#include <ostream>
#include <vector>
#include <random>
#include <glm\glm.hpp>


struct BlockType
{
	glm::vec3 color;

	BlockType(glm::vec3 color)
		: color(color){};
};

class Terrain
{
public:
	Terrain();
	~Terrain();

	uint16_t operator()(uint32_t x, uint32_t y);

	static const uint32_t WIDTH = 1000;
	static const uint32_t HEIGHT = 100;

	std::vector<BlockType> block_types;
private:
	
	std::vector<uint16_t> tiles;
	
};

