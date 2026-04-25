#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"
#include "components/rigidbody.h"

class GameObject;

class ShapeRenderable : public Component
{
public:
	explicit ShapeRenderable(GameObject* newOwner, sf::CircleShape polygonShape, sf::Color color);

	void Draw(sf::RenderWindow& window);

private:
	GameObject* owner = nullptr;
	sf::CircleShape shape;
};