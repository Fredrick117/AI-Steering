#include "rigidbody.h"

Rigidbody::Rigidbody(GameObject* newOwner)
{
	this->owner = newOwner;
}

void Rigidbody::Update(float deltaTime)
{
	velocity += steering.direction * deltaTime;

	if (owner == nullptr)
	{
		std::cout << "Rigidbody (Update): owner was nullptr!" << std::endl;
		return;
	}

	if (velocity.length() > maxSpeed)
	{
		velocity = velocity.normalized() * maxSpeed;
	}

	owner->position += velocity * deltaTime;
}
