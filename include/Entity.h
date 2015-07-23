#pragma once
#include <EntityType.h>

/// An Entity is a base game object
class Entity
{
public:
	Entity();
	~Entity();

	/// The type determines which kind of entity this is
	/// (see Type Object)
	EntityType type;
};

