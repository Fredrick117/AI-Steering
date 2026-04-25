#pragma once

#include "steeringbehavior.h"
#include "steeringoutput.h"

class FleeBehavior : public SteeringBehavior
{
public:
	FleeBehavior() = delete;
	FleeBehavior(GameObject* parent, float maxSpeed) : parent(parent), maxSpeed(maxSpeed) {};

	virtual SteeringOutput GetSteering() const override;
	const char* GetName() const override { return "Flee"; }
	void SetTarget(sf::Vector2f target) override;

private:
	sf::Vector2f target;
	GameObject* parent;
	float maxSpeed = 500.0f;
};