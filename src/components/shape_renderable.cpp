#include "shape_renderable.h"
#include "gameobject.h"
#include "utilities.h"

ShapeRenderable::ShapeRenderable(GameObject* newOwner, sf::CircleShape polygonShape, sf::Color color)
{
	owner = newOwner;
	shape = polygonShape;
	shape.setFillColor(color);
	shape.setScale(sf::Vector2f(0.2f, 0.2f));
	shape.setOrigin({ polygonShape.getRadius(), polygonShape.getRadius() });
}

void ShapeRenderable::Draw(sf::RenderWindow& window)
{
	shape.setPosition(owner->position);

	// TODO: what about setting the rotation of game objects that don't have a rigidbody?
	if (Rigidbody* rb = owner->GetComponent<Rigidbody>())
	{
		shape.setRotation(Utils::VectorToRotation(rb->velocity));
	}

	window.draw(shape);
}