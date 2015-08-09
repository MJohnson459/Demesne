#include "GameState.h"


GameState::GameState(Entity& player, uint32_t width, uint32_t height, const sf::Window& window)
	: camera(width, height, player), window(window)
{

}


GameState::~GameState()
{
}

void GameState::Update()
{
	camera.Update();
	terrain.Update();
}