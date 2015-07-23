#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <TerrainGraphicsComponent.h>
#include <PlayerController.h>
#include <PlayerGraphics.h>
#include <Entity.h>
#include <EntityType.h>
#include <PhysicsComponent.h>

/// Main class for the game
class Demesne
{
public:
	Demesne();
	~Demesne();

	/// Start the game running
	void Execute();
};

