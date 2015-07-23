#pragma once
#include <Entity.h>
#include <GameState.h>

/// An entities physics component
///
/// The PhysicsComponent will handle things like collision and status effects (ie gravity)
class PhysicsComponent
{
public:
	PhysicsComponent(Entity& entity);
	~PhysicsComponent();

	/// Update method expected to be called every frame
	void Update(GameState& state);

	void HandleCollision(glm::vec2 collision);

	/// The entity this PhysicsComponent acts upon (its owner)
	Entity& entity;
};

