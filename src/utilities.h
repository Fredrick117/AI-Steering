#pragma once

#include "boid/boid.h"
#include "components/rigidbody.h"
#include "components/shape_renderable.h"
#include "gameobject.h"

#include <vector>
#include <cmath>

namespace Utils 
{
	inline constexpr double PI = 3.14159265358979323846;

	// Returns true if the provided float is near zero (within 0.000001)
	inline bool IsNearZero(float num)
	{
		const float epsilon = 1e-6f;
		return std::abs(num) < epsilon;
	}

	// Returns whether the provided vector's components are exactly zero
	inline bool Vector2fIsZero(const sf::Vector2f& inVector)
	{
		return (inVector.x == 0.0f && inVector.y == 0.0f);
	}

	// Converts a vector to an SFML-readable angle (in radians)
	inline sf::Angle VectorToRotation(const sf::Vector2f& inVector)
	{
		return sf::radians(std::atan2(inVector.y, inVector.x));
	}

	// Spawns a boid at the mouse's position
	inline void SpawnBoidAtMousePosition(const sf::RenderWindow& window, std::vector<GameObject*>& gameObjects)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		Boid* newBoid = new Boid({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
		gameObjects.push_back(newBoid);
	}
}