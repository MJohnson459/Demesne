#include "Terrain.h"


Terrain::Terrain()
{

	block_types.push_back(BlockType(glm::vec3(1, 0, 0)));
	block_types.push_back(BlockType(glm::vec3(0, 1, 0)));
	block_types.push_back(BlockType(glm::vec3(0, 0, 1)));


	tiles.reserve(WIDTH*HEIGHT);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 2);

	for (int i = 0; i < WIDTH*HEIGHT; ++i)
	{
		tiles.push_back(distribution(generator));
	}
}


Terrain::~Terrain()
{
}

uint16_t Terrain::operator()(uint32_t x, uint32_t y)
{
	return tiles[x*Terrain::HEIGHT + y];
}
