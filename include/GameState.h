#pragma once
#include <Terrain.h>
#include <Camera.h>

#include <glm\glm.hpp>

class GameState
{
public:
	GameState();
	~GameState();

	Terrain terrain;
	Camera camera;
};

