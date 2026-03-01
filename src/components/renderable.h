#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"

class GameObject;

class Renderable : public Component
{
public:
	explicit Renderable(GameObject* newOwner, float circleRadius);

	// TODO: make this an sf::Sprite in the future
	sf::CircleShape sprite;

	void Draw(sf::RenderWindow& window);

private:
	GameObject* owner = nullptr;
};