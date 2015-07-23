#pragma once
#include "PhysicsComponent.h"
class TerrainPhysicsComponent
{
public:
	TerrainPhysicsComponent(Terrain& terrain);
	~TerrainPhysicsComponent();

	/// Check if a component is colliding with the terrain
	bool CheckCollision(PhysicsComponent& component);

private:
	Terrain& terrain;

	/// Check if a single point is colliding with terrain.
	///
	/// \param vec The point to check
	/// \param velocity The velocity of the point.
	/// \param [out] collision_vec The collision vector result based on the velocity.
	bool CheckPoint(glm::vec2 vec, const glm::vec3& velocity, glm::vec2& collision_vec);
};

