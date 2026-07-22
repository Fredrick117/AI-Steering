#include "arrive.h"

SteeringOutput ArriveBehavior::GetSteering()
{
	SteeringOutput steering;

	sf::Vector2f directionToTarget = this->target - this->parent->position;
	float distance = directionToTarget.length();

	Rigidbody* rigidbody = this->parent->GetComponent<Rigidbody>();

	if (distance < targetRadius)
	{
		return steering;
	}

	float rampedSpeed = this->maxSpeed * (distance / this->slowRadius);
	float clippedSpeed = std::min(rampedSpeed, this->maxSpeed);

	/*float targetSpeed;
	if (distance > slowRadius)
	{
		targetSpeed = maxSpeed;
	}
	else
	{
		targetSpeed = maxSpeed * (distance / slowRadius);
	}*/

	//sf::Vector2f targetVelocity = (directionToTarget / distance) * targetSpeed;
	sf::Vector2f targetVelocity = (clippedSpeed / distance) * directionToTarget;

	steering.direction = targetVelocity - rigidbody->velocity;

	return steering;
}

void ArriveBehavior::SetTarget(sf::Vector2f target)
{
	this->target = target;
}
