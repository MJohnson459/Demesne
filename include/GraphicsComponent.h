#pragma once

#include <GameState.h>

/// Abstract class which renders an Entity
class GraphicsComponent
{
public:
	GraphicsComponent();
	~GraphicsComponent();

	/// Render an entity
	virtual void Render(GameState& state) = 0;
};

