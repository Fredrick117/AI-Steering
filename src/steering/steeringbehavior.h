#pragma once

#include "components/component.h"
#include "steeringoutput.h"
#include "gameobject.h"

class SteeringBehavior : public Component
{
public:
	virtual ~SteeringBehavior() = default;
	virtual SteeringOutput GetSteering() const = 0;
	virtual const char* GetName() const = 0;
	virtual void SetTarget(sf::Vector2f) {}
};