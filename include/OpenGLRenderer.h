#pragma once
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GameState.h>

class OpenGLRenderer
{
public:
	OpenGLRenderer(sf::Window& window);
	~OpenGLRenderer();

	void Render(GameState& state);
private:
	sf::Window& window;

	void RenderTerrain(Terrain& terrain);
};

