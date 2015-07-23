#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(Entity& entity)
	:entity(entity)
{
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(GameState& state)
{
	glm::vec3 gravity(0.0f, -0.03f, 0.0f);
	entity.velocity += gravity;
	entity.position += entity.velocity;
}

void PhysicsComponent::HandleCollision(glm::vec2 collision)
{
	if (collision[0] != 0 && entity.velocity[0] > 0)
	{
		entity.position[0] = ceil(entity.position[0] - entity.velocity[0]);
		entity.velocity[0] = 0;
	}

	if (collision[0] != 0 && entity.velocity[0] < 0)
	{
		entity.position[0] = floor(entity.position[0] - entity.velocity[0]);
		entity.velocity[0] = 0;
	}

	if (collision[1] != 0 && entity.velocity[1] > 0)
	{
		entity.position[1] = ceil(entity.position[1] - entity.velocity[1]);
		entity.velocity[1] = 0;
	}

	if (collision[1] != 0 && entity.velocity[1] < 0)
	{
		entity.position[1] = floor(entity.position[1] - entity.velocity[1]);
		entity.velocity[1] = 0;
	}
}