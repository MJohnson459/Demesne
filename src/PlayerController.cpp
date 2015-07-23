#include "PlayerController.h"


PlayerController::PlayerController(Entity& entity)
	:entity(entity)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Update(GameState& state)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		entity.position[0] -= 0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		entity.position[0] += 0.005f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		entity.position[1] += 0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		entity.position[1] -= 0.005f;
	}

}