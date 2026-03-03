#include "seek.h"

SteeringOutput SeekBehavior::GetSteering() const
{
	SteeringOutput steering;

	if (target.x != 0.0f && target.y != 0.0f)
	{
		sf::Vector2f direction = target - parent->position;
		direction = direction.normalized();
		steering.direction = direction * maxSpeed;

		return steering;
	}

	return steering;
}

void SeekBehavior::SetTarget(sf::Vector2f target)
{
	this->target = target;
}