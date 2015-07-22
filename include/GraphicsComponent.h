#pragma once

#include <GameState.h>

class GraphicsComponent
{
public:
	GraphicsComponent();
	~GraphicsComponent();

	void Render(GameState* gs);
};

