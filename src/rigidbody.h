#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "gameobject.h"
#include "component.h"
#include "steeringoutput.h"

class GameObject;

class Rigidbody : public Component
{
public:
	explicit Rigidbody(GameObject* newOwner);

	sf::Vector2f velocity = { 0.0f, 0.0f };

	float maxSpeed = 100.0f;
	float angularSpeed = 0.0f;

	float maxAcceleration = 100.0f;
	float maxAngularAcceleration = 30.0f;

	SteeringOutput steering;

	void Update(float deltaTime) override;

private:
	int id = 0;

	GameObject* owner = nullptr;
};