#include "steeringbehavior.h"
#include "rigidbody.h"

SteeringOutput SeekBehavior::GetSteering() const
{
	SteeringOutput steering;

	sf::Vector2f targetPosition = target;

	if (targetPosition.x != 0.0f && targetPosition.y != 0.0f)
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
