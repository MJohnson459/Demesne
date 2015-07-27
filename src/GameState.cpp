#include "GameState.h"


GameState::GameState(Entity& player, uint32_t width, uint32_t height)
	: camera(width, height, player)
{

}


GameState::~GameState()
{
}
