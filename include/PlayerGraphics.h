#pragma once
#include "GraphicsComponent.h"
#include <Entity.h>

/// The graphics component of the player entity
class PlayerGraphics :
	public GraphicsComponent
{
public:
	PlayerGraphics(Entity& entity);
	~PlayerGraphics();

	/// Render the player
	void Render(GameState& state);

private:
	/// The player entity
	Entity& entity;
};

