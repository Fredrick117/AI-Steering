#pragma once

#include <vector>
#include <iostream>
#include "steeringbehavior.h"
#include "steeringoutput.h"

class Boid;

class FlockBehavior : public SteeringBehavior
{
public:
	FlockBehavior() = delete;
	FlockBehavior(Boid* parent, const std::vector<Boid*>* flock, float maxSpeed)
		: parent(parent), flock(flock), maxSpeed(maxSpeed) {};

	virtual SteeringOutput GetSteering() const override;
	const char* GetName() const override { return "Flock"; }

	float neighborRadius = 150.0f;
	float separationRadius = 40.0f;

	float alignmentWeight = 1.0f;
	float cohesionWeight = 1.0f;
	float separationWeight = 1.5f;

private:
	Boid* parent;
	const std::vector<Boid*>* flock;
	float maxSpeed;
};
