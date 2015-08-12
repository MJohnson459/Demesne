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
			//tiles.push_back(distribution(rand));
			tiles.push_back(1);
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

size_t Terrain::GetIndex(glm::vec2 pos) const
{
	pos[0] = floor(pos[0]);
	pos[1] = floor(pos[1]);

	pos[0] += WIDTH / 2;
	pos[1] += HEIGHT / 2;

	if (pos[0] >= WIDTH) pos[0] = WIDTH - 1;
	if (pos[1] >= HEIGHT) pos[1] = HEIGHT - 1;

	return pos[0]*Terrain::HEIGHT + pos[1];
}

void Terrain::Set(int x, int y, uint16_t type)
{
	Set(glm::vec2(x, y), type);
}
void Terrain::Set(glm::vec2 pos, uint16_t type)
{
	size_t index = GetIndex(pos);

	if (tiles[index] != type)
	{
		printf("Setting tile (%f,%f) to %i\n", pos[0], pos[1], type);
		tiles[index] = type;
		updated.push_back(pos);
	}
}

void Terrain::Update()
{
}