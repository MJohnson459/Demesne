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

private:
	/// The player entity
	Entity& entity;

	bool jumping;
};

