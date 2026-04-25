#include "boid.h"
#include "components/rigidbody.h"
#include "steering/steeringbehavior.h"
#include "steering/seek.h"
#include "steering/flee.h"
#include "steering/wander.h"
#include "steering/arrive.h"

constexpr auto BOID_RADIUS = 60.0f;

Boid::Boid()
{
	auto addBehavior = [&](SteeringBehavior* b) {
		this->AddComponent(b);
		steeringBehaviors.push_back(b);
	};

	addBehavior(new SeekBehavior(this, 500.0f));
	addBehavior(new FleeBehavior(this, 500.0f));
	addBehavior(new WanderBehavior(500.0f));
	addBehavior(new ArriveBehavior(this, 500.0f, 10.0f, 25.0f));

	this->SetCurrentSteeringBehavior(0);

	this->AddComponent(new Rigidbody(this));
	this->AddComponent(new ShapeRenderable(this, sf::CircleShape(BOID_RADIUS), sf::Color::Cyan));
}

Boid::Boid(sf::Vector2f spawnPosition)
{
	auto addBehavior = [&](SteeringBehavior* b) {
		this->AddComponent(b);
		steeringBehaviors.push_back(b);
	};

	addBehavior(new SeekBehavior(this, 500.0f));
	addBehavior(new FleeBehavior(this, 500.0f));
	addBehavior(new WanderBehavior(500.0f));
	addBehavior(new ArriveBehavior(this, 500.0f, 10.0f, 25.0f));

	this->SetCurrentSteeringBehavior(0);

	this->AddComponent(new Rigidbody(this));
	this->AddComponent(new ShapeRenderable(this, sf::CircleShape(BOID_RADIUS), sf::Color::Cyan));
	this->position = spawnPosition;
}

void Boid::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (this->behaviorData != nullptr)
	{
		this->GetComponent<Rigidbody>()->steering = this->behaviorData->GetSteering();
	}

	sf::Vector2 v = this->GetComponent<Rigidbody>()->velocity;
	if (!Utils::Vector2fIsZero(v))
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

void Boid::SetCurrentSteeringBehavior(int index)
{
	if (index >= 0 && index < static_cast<int>(steeringBehaviors.size()))
		this->behaviorData = steeringBehaviors[index];
}

std::vector<const char*> Boid::GetBehaviorNames() const
{
	std::vector<const char*> names;
	for (auto* b : steeringBehaviors)
		names.push_back(b->GetName());
	return names;
}
