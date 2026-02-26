#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"

class GameObject;

class Renderable : public Component
{
public:
	explicit Renderable(GameObject* newOwner, float circleRadius);

	sf::CircleShape sprite;

	void Draw(sf::RenderWindow& window);

private:
	GameObject* owner = nullptr;
};