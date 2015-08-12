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

	/// Update player state
	void Update(GameState& state);

	/// Respond to key pressed events
	void HandleKeyPressed(sf::Keyboard::Key key);
	/// Respond to key released events
	void HandleKeyReleased(sf::Keyboard::Key key);

private:
	/// The player entity
	Entity& entity;

	/// Check if thruster is firing
	bool jumping;

	/// Max speed horizontally
	float maxSpeedX;
	/// Max speed vertically
	float maxSpeedY;

	/// Max thruster time
	float maxHover;
	/// Seconds of fuel remaining
	float remainingHover;
};

