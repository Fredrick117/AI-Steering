#pragma once

#include <SFML/Graphics.hpp>

#include "component.h"

class GameObject;

class Renderable : public Component
{
public:
	explicit Renderable(GameObject* newOwner, const std::string& texturePath);

	sf::Sprite sprite;

	void Draw(sf::RenderWindow& window);

private:
	GameObject* owner = nullptr;
	sf::Texture texture;
};