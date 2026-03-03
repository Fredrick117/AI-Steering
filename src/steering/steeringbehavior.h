#pragma once

#include "components/component.h"
#include "steeringoutput.h"
#include "gameobject.h"

class SteeringBehavior : public Component
{
public:
	virtual ~SteeringBehavior() = default;
	virtual SteeringOutput GetSteering() const = 0;
};