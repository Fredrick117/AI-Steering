#pragma once

#include "steeringbehavior.h"
#include "steeringoutput.h"

class SeekBehavior : public SteeringBehavior
{
public:
	SeekBehavior() = delete;
	SeekBehavior(GameObject* parent, float maxSpeed) : parent(parent), maxSpeed(maxSpeed) {};

	virtual SteeringOutput GetSteering() const override;
	const char* GetName() const override { return "Seek"; }
	void SetTarget(sf::Vector2f target) override;

private:
	sf::Vector2f target;
	GameObject* parent;
	float maxSpeed = 500.0f;
};