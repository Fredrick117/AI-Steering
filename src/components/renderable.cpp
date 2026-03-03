#include "renderable.h"
#include "gameobject.h"
#include "component.h"

Renderable::Renderable(GameObject* newOwner, float circleRadius)
{
	this->owner = newOwner;

	sprite = sf::CircleShape(circleRadius);
	sprite.setFillColor(sf::Color::Red);
}

void Renderable::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(GetOwner().position);
	window.draw(sprite);
}
