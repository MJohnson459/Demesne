#include "TerrainPhysicsComponent.h"


TerrainPhysicsComponent::TerrainPhysicsComponent(Terrain& terrain)
	: terrain(terrain)
{
}


TerrainPhysicsComponent::~TerrainPhysicsComponent()
{
}

bool TerrainPhysicsComponent::CheckCollision(PhysicsComponent& component)
{
	glm::vec2 collision_vec;

	bool collision = false;

	if (CheckPoint(glm::vec2(component.entity.position[0], component.entity.position[1]), component.entity.velocity, collision_vec)) {
		collision = true;
	}

	if (CheckPoint(glm::vec2(component.entity.position[0] + component.entity.size[0], component.entity.position[1]), component.entity.velocity, collision_vec)) {
		collision = true;
	}

	if (CheckPoint(glm::vec2(component.entity.position[0] + component.entity.size[0], component.entity.position[1] + component.entity.size[1]), component.entity.velocity, collision_vec)) {
		collision = true;
	}

	if (CheckPoint(glm::vec2(component.entity.position[0], component.entity.position[1] + component.entity.size[1]), component.entity.velocity, collision_vec)) {
		collision = true;
	}

	if (collision)
		component.HandleCollision(collision_vec);

	return false;
}

bool TerrainPhysicsComponent::CheckPoint(glm::vec2 vec, const glm::vec3& velocity, glm::vec2& collision_vec)
{
	// No collision
	if (terrain(vec) == 0) return false;
		
	if (terrain(vec - glm::vec2(0, velocity[1])) == 0)
	{
		collision_vec += glm::vec2(0, 1);
		return true;
	}

	if (terrain(vec - glm::vec2(velocity[0], 0)) == 0)
	{
		collision_vec += glm::vec2(1, 0);
		return true;
	}

	// Both x and y aren't clear
	collision_vec += glm::vec2(1, 1);
	return true;
}