#include "PlayerController.h"


PlayerController::PlayerController(Entity& entity)
	: entity(entity)
	, jumping(false)
	, maxSpeedX(0.2)
	, maxSpeedY(1.0)
	, maxHover(1)
	, remainingHover(maxHover)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Update(GameState& state)
{
	if (jumping)
	{
		// Hover
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && remainingHover > 0)
		{
			entity.velocity[1] += 0.03;
			remainingHover -= 0.01; // Called every 10 ms so remove 10ms of fuel
			printf("hovering! %1.2fs,  %1.2fm/s\n", remainingHover, entity.velocity[1]);
		}

		// If we aren't moving vertically then reset jump
		if (entity.velocity[1] == 0)
		{
			jumping = false;
			entity.acceleration[1] = 0;
			remainingHover = maxHover;
		}
	}
	



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
	entity.velocity[1] += entity.acceleration[1];


	// Cap speeds
	if (entity.velocity[0] > maxSpeedX) entity.velocity[0] = maxSpeedX;
	if (entity.velocity[0] < -maxSpeedX) entity.velocity[0] = -maxSpeedX;

	if (entity.velocity[1] > maxSpeedY) entity.velocity[1] = maxSpeedY;
	if (entity.velocity[1] < -maxSpeedY) entity.velocity[1] = -maxSpeedY;


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(state.window);
		glm::vec2 click_pos = state.camera.ScreenToWorld(position.x, position.y);

		state.terrain.Set(click_pos, 2);

		//printf("Click - x: %f, y: %f\n", click_pos[0], click_pos[1]);
	}


}

void PlayerController::HandleKeyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Space && !jumping)
	{
		jumping = true;
	}
}

void PlayerController::HandleKeyReleased(sf::Keyboard::Key key)
{
}