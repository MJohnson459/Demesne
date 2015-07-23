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
	glm::vec3 gravity(0.0f, -0.002f, 0.0f);
	entity.position += gravity;
}