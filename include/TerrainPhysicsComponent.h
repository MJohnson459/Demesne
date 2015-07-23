#pragma once
#include "PhysicsComponent.h"
class TerrainPhysicsComponent
{
public:
	TerrainPhysicsComponent(Terrain& terrain);
	~TerrainPhysicsComponent();

	bool CheckCollision(PhysicsComponent& component);

private:
	Terrain& terrain;

	bool CheckPoint(glm::vec2 vec, const glm::vec3& velocity, glm::vec2& collision_vec);
};

