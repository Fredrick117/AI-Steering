#pragma once

#include <SFML/Graphics.hpp>

#include "gameobject.h"
#include "steering/steeringoutput.h"
#include "steering/steeringbehavior.h"

class Rigidbody;

class Boid : public GameObject
{
public:
	Boid();

	void Update(float deltaTime) override;

	bool HasReachedDestination(sf::Vector2f destination, float tolerance);

	float maxSpeed = 500.0f;

	sf::Vector2f targetPosition;
};