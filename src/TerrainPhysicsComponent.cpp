#include "TerrainPhysicsComponent.h"


TerrainPhysicsComponent::TerrainPhysicsComponent(Terrain& terrain)
	: terrain(terrain)
{
}


TerrainPhysicsComponent::~TerrainPhysicsComponent()
{
}


/// When checking the collision between the terrain and a component
/// we check the 4 corners of the object and make sure they don't intersect
/// a non-0 terrain block.
///
/// This method doesn't really work properly if the component is larger than 1x1
/// as it would be possible to collide with the terrain without any corner colliding.
///
/// \todo Implemement this in a more generic/correct manner
///
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


/// This method prioritises the y axis over x in that it will attempt to fix a collision
/// by undoing the y velocity first.
///
/// This might cause problems later on.
///
bool TerrainPhysicsComponent::CheckPoint(glm::vec2 vec, const glm::vec3& velocity, glm::vec2& collision_vec)
{
	// No collision
	if (terrain(vec) == 0) return false;
		
	// Check y velocity
	if (terrain(vec - glm::vec2(0, velocity[1])) == 0)
	{
		collision_vec += glm::vec2(0, 1);
		return true;
	}

	// Check x velocity
	if (terrain(vec - glm::vec2(velocity[0], 0)) == 0)
	{
		collision_vec += glm::vec2(1, 0);
		return true;
	}

	// Neither x and y are clear
	collision_vec += glm::vec2(1, 1);
	return true;
}