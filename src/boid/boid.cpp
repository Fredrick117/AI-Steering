#include "boid.h"
#include "components/rigidbody.h"
#include "steering/steeringbehavior.h"
#include "steering/seek.h"
#include "steering/flee.h"

Boid::Boid()
{
	this->AddComponent(new SeekBehavior(this, 500.0f));
	this->AddComponent(new FleeBehavior(this, 500.0f));
}

void Boid::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	this->GetComponent<Rigidbody>()->steering = this->GetComponent<SeekBehavior>()->GetSteering();
}

bool Boid::HasReachedDestination(sf::Vector2f destination, float tolerance)
{
	float dx = destination.x - this->position.x;
	float dy = destination.y - this->position.y;
	return std::sqrt(dx * dx + dy * dy) <= tolerance;
}
