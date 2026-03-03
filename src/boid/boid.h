#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "gameobject.h"
#include "steering/steeringoutput.h"
#include "steering/steeringbehavior.h"

class Rigidbody;

enum class Behavior
{
	SEEK = 0,
	FLEE = 1
};

class Boid : public GameObject
{
public:
	Boid();

	void Update(float deltaTime) override;

	bool HasReachedDestination(sf::Vector2f destination, float tolerance);

	float maxSpeed = 500.0f;

	sf::Vector2f targetPosition;

	bool debugEnabled = true;
	std::array<sf::Vertex, 2> debugDirectionLine;
	void DrawDebug(sf::RenderWindow& window);

	SteeringBehavior* GetCurrentSteeringBehavior();
	void SetCurrentSteeringBehavior(Behavior newBehavior);

private:
	SteeringBehavior* currentBehavior = nullptr;
};