#pragma once

#include <random>
#include <math.h>

#include "steeringbehavior.h"
#include "steeringoutput.h"
#include "utilities.h"

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior() = delete;
	WanderBehavior(float maxSpeed) : maxSpeed(maxSpeed) {};

	virtual SteeringOutput GetSteering() override;
	const char* GetName() const override { return "Wander"; }

private:
	float maxSpeed = 500.0f;	// TODO: make this a property in SteeringBehavior?
};