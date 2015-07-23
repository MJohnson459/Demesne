#pragma once
#include <GameState.h>

/// Abstract class for controller components
///
/// Controller components are what defines the behaviour of an entity.
class ControllerComponent
{
public:
	ControllerComponent();
	~ControllerComponent();

	/// Virtual method to update every frame
	virtual void Update(GameState& state) = 0;
};

