#pragma once
#include <stdint.h>
#include <ostream>
#include <vector>
#include <random>
#include <glm/glm.hpp>
#include <Entity.h>

#include <noise/noise.h>

/// Struct which stores all the information about a particular block type
struct BlockType
{
	static uint16_t MAX_ID;
	uint16_t id;
	glm::vec3 color;

	BlockType(glm::vec3 color)
		: color(color){
		id = MAX_ID++;
	};
};

/// Holds an array representing the terrain
class Terrain
{
public:
	Terrain();
	~Terrain();

	/// Get block type at (x,y)
	uint16_t& operator()(int x, int y);

	/// Get block type at (x,y)
	uint16_t& operator()(glm::vec2 vec);

	/// Width of the terrain
	static const uint32_t WIDTH = 1000;

	/// Height of the terrain
	static const uint32_t HEIGHT = 200;

	/// A vector of the currently loaded block types
	std::vector<BlockType> block_types;
private:
	
	/// The array storing the terrain
	std::vector<uint16_t> tiles;

	void GenerateTerrain();

	int GenHeight(int x, noise::module::Blend& blend) const;
	
};

