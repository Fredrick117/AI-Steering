#include "flee.h"

SteeringOutput FleeBehavior::GetSteering()
{
	SteeringOutput steering;

	if (target.x != 0.0f && target.y != 0.0f)
	{
		sf::Vector2f direction = parent->position - target;
		direction = direction.normalized();
		steering.direction = direction * maxSpeed;

		return steering;
	}

	return steering;
}

void FleeBehavior::SetTarget(sf::Vector2f target)
{
	this->target = target;
}