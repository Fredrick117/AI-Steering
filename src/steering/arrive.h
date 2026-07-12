#pragma once

#include "components/rigidbody.h"
#include "steeringbehavior.h"
#include "steeringoutput.h"
#include "utilities.h"

#include <algorithm>

class ArriveBehavior : public SteeringBehavior
{
public:
	ArriveBehavior() = delete;
	ArriveBehavior(GameObject* parent, float maxSpeed, float slowRadius, float targetRadius)
		: parent(parent), maxSpeed(maxSpeed), slowRadius(slowRadius), targetRadius(targetRadius) {};

	virtual SteeringOutput GetSteering() override;
	const char* GetName() const override { return "Arrive"; }
	void SetTarget(sf::Vector2f target) override;

private:
	sf::Vector2f target;
	GameObject* parent;
	float maxSpeed;
	float slowRadius;
	float targetRadius;
};
