#include "Terrain.h"


Terrain::Terrain()
{

	block_types.push_back(BlockType(glm::vec3(0.1f, 0.4f, 0.8f)));
	block_types.push_back(BlockType(glm::vec3(0, 1, 0)));
	block_types.push_back(BlockType(glm::vec3(0, 0, 1)));
	block_types.push_back(BlockType(glm::vec3(1, 0, 0)));
	block_types.push_back(BlockType(glm::vec3(1, 0, 1)));


	tiles.reserve(WIDTH*HEIGHT);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 2);

	for (int i = 0; i < WIDTH*HEIGHT/2; ++i)
	{
		tiles.push_back(distribution(generator));
	}

	for (int i = WIDTH*HEIGHT / 2; i < WIDTH*HEIGHT; ++i)
	{
		tiles.push_back(0);
	}

	operator()(-1, 0) = 3;
}


Terrain::~Terrain()
{
}

uint16_t& Terrain::operator()(int x, int y)
{
	x += WIDTH / 2;
	y += HEIGHT / 2;

	if (x >= WIDTH) x = WIDTH-1;
	if (y >= HEIGHT) y = HEIGHT-1;

	return tiles[y*Terrain::WIDTH + x];
}

uint16_t& Terrain::operator()(glm::vec2 vec)
{
	return operator()(floor(vec[0]), floor(vec[1]));
}
