#pragma once
#include <EntityType.h>
#include <glm/glm.hpp>

/// An Entity is a base game object
/// 
/// It should only contain data that needs to be shared between components
class Entity
{
public:
	Entity(glm::vec3 position = glm::vec3(), glm::vec2 size = glm::vec2(2,4));
	~Entity();

	/// The type determines which kind of entity this is
	/// (see Type Object)
	EntityType type;

	glm::vec3 position;
	glm::vec2 size;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

