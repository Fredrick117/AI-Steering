#include "renderable.h"
#include "gameobject.h"
#include "component.h"

#include <iostream>

Renderable::Renderable(GameObject* newOwner, const std::string& texturePath) : texture(texturePath), sprite(texture)
{
	this->owner = newOwner;

	/*if (!this->texture.loadFromFile("img/boid.png"))
	{
		std::cout << "ERROR: couldn't load texture!" << std::endl;
	}

	sprite = sf::Sprite(texture);*/
}

void Renderable::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(GetOwner().position);
	window.draw(sprite);
}
