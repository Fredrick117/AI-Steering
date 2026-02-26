#include "rigidbody.h"

Rigidbody::Rigidbody(GameObject* newOwner)
{
	this->owner = newOwner;
}

void Rigidbody::Update(float deltaTime)
{
	this->velocity += steering.direction * deltaTime;

	if (owner == nullptr)
	{
		std::cout << "Rigidbody (Update): owner was nullptr!" << std::endl;
		return;
	}

	owner->position += velocity * deltaTime;

	if (this->velocity.length() > maxSpeed)
	{
		this->velocity = this->velocity.normalized();
		this->velocity *= maxSpeed;
	}
}
