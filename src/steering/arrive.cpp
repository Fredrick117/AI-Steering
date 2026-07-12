#include "arrive.h"

SteeringOutput ArriveBehavior::GetSteering()
{
	SteeringOutput steering;

	sf::Vector2f directionToTarget = this->target - this->parent->position;
	float distance = directionToTarget.length();

	Rigidbody* rigidbody = this->parent->GetComponent<Rigidbody>();

	if (targetRadius < distance)
	{
		rigidbody->velocity = sf::Vector2f(0.0f, 0.0f);
		return steering;
	}

	float rampedSpeed = this->maxSpeed * (distance / this->slowRadius);
	float clippedSpeed = std::min(rampedSpeed, this->maxSpeed);

	steering.direction = (clippedSpeed / distance) * directionToTarget;
	steering.direction -= rigidbody->velocity;

	std::cout << "Steering.direction.x = " << steering.direction.x << std::endl;
	std::cout << "Steering.direction.y = " << steering.direction.y << std::endl;

	return steering;
}

void ArriveBehavior::SetTarget(sf::Vector2f target)
{
	this->target = target;
}
