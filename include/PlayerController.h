#pragma once
#include "ControllerComponent.h"
#include <Entity.h>
#include <GameState.h>

/// The PlayerController class will handle all of the input and move the player entity accordingly
class PlayerController :
	public ControllerComponent
{
public:
	PlayerController(Entity& entity);
	~PlayerController();

	void Update(GameState& state);

	void HandleKeyPressed(sf::Keyboard::Key key);

	void HandleKeyReleased(sf::Keyboard::Key key);

private:
	/// The player entity
	Entity& entity;

	bool jumping;

	float maxSpeedX;
	float maxSpeedY;

	float maxHover;
	float remainingHover;
};

