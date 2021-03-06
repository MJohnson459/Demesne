#pragma once
#include <Terrain.h>
#include <Camera.h>

#include <glm\glm.hpp>

/// This class holds the state of the world.
class GameState
{
public:
	GameState(Entity& player, uint32_t width, uint32_t height, const sf::Window& window);
	~GameState();

	/// Save the current game state
	void Save(std::string file);

	/// Load a previously saved game state
	void Load(std::string file);

	void Update();

	/// The current world loaded
	Terrain terrain;

	/// The current view
	Camera camera;

	const sf::Window& window;
};

