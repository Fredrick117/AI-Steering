#pragma once

#include "component.h"
#include "steeringoutput.h"
#include "gameobject.h"

class SteeringBehavior : public Component
{
public:
	virtual ~SteeringBehavior() = default;
	virtual SteeringOutput GetSteering() const = 0;
};

class SeekBehavior : public SteeringBehavior
{
public:
	SeekBehavior() = delete;
	SeekBehavior(GameObject* parent, float maxSpeed) : parent(parent), maxSpeed(maxSpeed) {};

	virtual SteeringOutput GetSteering() const override;
	void SetTarget(sf::Vector2f target);

private:
	sf::Vector2f target;
	GameObject* parent;
	float maxSpeed = 500.0f;
};

class FleeBehavior : public SteeringBehavior
{
public:
	FleeBehavior() = delete;
	FleeBehavior(GameObject* parent, float maxSpeed) : parent(parent), maxSpeed(maxSpeed) {};

private:
	sf::Vector2f target;
	GameObject* parent;
	float maxSpeed = 500.0f;
};