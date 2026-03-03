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

	switch (currentBehavior)
	{
	case Behavior::SEEK:
		this->GetComponent<Rigidbody>()->steering = this->GetComponent<SeekBehavior>()->GetSteering();
		break;
	case Behavior::FLEE:
		this->GetComponent<Rigidbody>()->steering = this->GetComponent<FleeBehavior>()->GetSteering();
		break;
	}

	sf::Vector2 v = this->GetComponent<Rigidbody>()->velocity;
	if (v.x != 0.0f && v.y != 0.0f)
	{
		v = v.normalized();
	}

	//std::cout << "Velocity: (" << std::to_string(v.x) << ", " << std::to_string(v.y) << ")" << std::endl;

	debugDirectionLine =
	{
		sf::Vertex{ this->position },
		sf::Vertex{ this->position + (v * 20.0f) },
	};

	//std::cout << "Position: (" << std::to_string(this->position.x) << ", " << std::to_string(this->position.y) << ")" << std::endl;
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
