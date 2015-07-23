#include "PlayerController.h"


PlayerController::PlayerController(Entity& entity)
	: entity(entity)
	, jumping(false)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Update(GameState& state)
{
	entity.velocity = glm::vec3();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		entity.velocity[0] = -0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		entity.velocity[0] = 0.005f;
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		entity.velocity[1] = -0.005f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		jumping = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		entity.velocity[1] = 0.0055f;
	}
}