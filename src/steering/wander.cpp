#include "wander.h"

SteeringOutput WanderBehavior::GetSteering()
{
	float phi = rand() * (2.0 * Utils::PI) / RAND_MAX;

	float x = cos(phi);
	float y = sin(phi);
	
	SteeringOutput steering;
	steering.direction = { x, y };
	steering.direction *= maxSpeed;

	return steering;
}