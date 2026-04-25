#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

#include "gameobject.h"
#include "steering/steeringoutput.h"
#include "steering/steeringbehavior.h"

class Rigidbody;

class Boid : public GameObject
{
public:
	Boid();
	Boid(sf::Vector2f spawnPosition);

	~Boid();

	void Update(float deltaTime) override;

	bool HasReachedDestination(sf::Vector2f destination, float tolerance);

	float maxSpeed = 500.0f;

	sf::Vector2f targetPosition;

	bool debugEnabled = false;
	std::array<sf::Vertex, 2> debugDirectionLine;
	void DrawDebug(sf::RenderWindow& window);

	SteeringBehavior* GetCurrentSteeringBehavior();
	void SetCurrentSteeringBehavior(int index);

	std::vector<const char*> GetBehaviorNames() const;

	int currentBehavior = 0;

	std::vector<SteeringBehavior*> steeringBehaviors;

private:
	SteeringBehavior* behaviorData = nullptr;
};