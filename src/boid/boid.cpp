#include "boid.h"
#include "components/rigidbody.h"
#include "steering/steeringbehavior.h"
#include "steering/seek.h"
#include "steering/flee.h"
#include "steering/wander.h"

Boid::Boid()
{
	this->AddComponent(new SeekBehavior(this, 500.0f));
	this->AddComponent(new FleeBehavior(this, 500.0f));
	this->AddComponent(new WanderBehavior(500.0f));

	this->SetCurrentSteeringBehavior(Behavior::SEEK);
}

void Boid::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (this->behaviorData != nullptr)
	{
		this->GetComponent<Rigidbody>()->steering = this->behaviorData->GetSteering();
	}

	sf::Vector2 v = this->GetComponent<Rigidbody>()->velocity;
	if (v.x != 0.0f && v.y != 0.0f)
	{
		v = v.normalized();
	}

	debugDirectionLine =
	{
		sf::Vertex{ this->position },
		sf::Vertex{ this->position + (v * 20.0f) },
	};
}

bool Boid::HasReachedDestination(sf::Vector2f destination, float tolerance)
{
	float dx = destination.x - this->position.x;
	float dy = destination.y - this->position.y;
	return std::sqrt(dx * dx + dy * dy) <= tolerance;
}

void Boid::DrawDebug(sf::RenderWindow& window)
{
	window.draw(this->debugDirectionLine.data(), this->debugDirectionLine.size(), sf::PrimitiveType::Lines);
}

SteeringBehavior* Boid::GetCurrentSteeringBehavior()
{
	return this->behaviorData;
}

void Boid::SetCurrentSteeringBehavior(Behavior newBehavior)
{
	switch (newBehavior)
	{
	case Behavior::SEEK:
		this->behaviorData = this->GetComponent<SeekBehavior>();
		break;
		
	case Behavior::FLEE:
		this->behaviorData = this->GetComponent<FleeBehavior>();
		break;
	case Behavior::WANDER:
		this->behaviorData = this->GetComponent<WanderBehavior>();
		break;
	}
}
