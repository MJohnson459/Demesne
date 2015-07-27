#include "Terrain.h"

uint16_t BlockType::MAX_ID = 0;

Terrain::Terrain()
{

	block_types.push_back(BlockType(glm::vec3(0.1f, 0.4f, 0.8f)));
	block_types.push_back(BlockType(glm::vec3()));
	block_types.push_back(BlockType(glm::vec3()));
	block_types.push_back(BlockType(glm::vec3()));
	block_types.push_back(BlockType(glm::vec3()));


	GenerateTerrain();

	operator()(0, -1) = 3;
	operator()(1, -1) = 3;
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

	return tiles[x*Terrain::HEIGHT + y];
}

uint16_t& Terrain::operator()(glm::vec2 vec)
{
	return operator()(floor(vec[0]), floor(vec[1]));
}


void Terrain::GenerateTerrain()
{
	
	std::default_random_engine rand;
	std::uniform_int_distribution<int> distribution(1, 2);
	tiles.reserve(WIDTH*HEIGHT);

	// see http://libnoise.sourceforge.net/docs/index.html
	noise::module::Perlin perlinHigh;
	noise::module::Perlin perlinLow;
	noise::module::Perlin perlinControl;
	noise::module::Blend blend;

	// This isnt really doing much but could be extended to create better terrain
	// with biomes etc
	blend.SetSourceModule(0, perlinHigh);
	blend.SetSourceModule(1, perlinLow);
	blend.SetControlModule(perlinControl);

	perlinHigh.SetFrequency(0.5);
	perlinHigh.SetOctaveCount(2);

	perlinLow.SetFrequency(2);
	perlinLow.SetOctaveCount(2);


	for (int i = 0; i < WIDTH; ++i)
	{
		int h = GenHeight(i, blend); 

		//printf("h: %d \n", h);
		for (int j = 0; j < h; ++j)
		{
			tiles.push_back(distribution(rand));
		}

		for (int j = h; j < HEIGHT; ++j)
		{
			tiles.push_back(0);
		}
		
	}
}

int Terrain::GenHeight(int x, noise::module::Blend& blend) const {
	double result = 0.0;
	
	double i = x * (1.0 / WIDTH);

	//printf("i: %f\n", i);

	result += blend.GetValue(i, 0, 0);

	result = (result/2.0 + 0.5) * (double)HEIGHT;

	return result > HEIGHT ? HEIGHT : result;
}