#include "PlayerController.h"


PlayerController::PlayerController(Entity& entity)
	: entity(entity)
	, jumping(false)
	, maxSpeed(0.2)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Update(GameState& state)
{
	entity.acceleration[0] = -entity.velocity[0] / 5.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && entity.acceleration[0] > -0.005f)
	{
		entity.acceleration[0] = -0.005f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && entity.acceleration[0] < 0.005f)
	{
		entity.acceleration[0] = 0.005f;
	}

	entity.velocity[0] += entity.acceleration[0];

	if (entity.velocity[0] > maxSpeed) entity.velocity[0] = maxSpeed;
	if (entity.velocity[0] < -maxSpeed) entity.velocity[0] = -maxSpeed;
}

void PlayerController::HandleKeyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Space && !jumping)
	{
		entity.velocity[1] += 0.5f;
		jumping = true;
	}
}

void PlayerController::HandleKeyReleased(sf::Keyboard::Key key)
{

	if (key == sf::Keyboard::Space)
	{
		jumping = false;
	}
}