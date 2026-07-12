#include "flock.h"
#include "boid/boid.h"

#include <cassert>

SteeringOutput FlockBehavior::GetSteering()
{
	SteeringOutput steering;

	sf::Vector2f alignment = Alignment().direction;
	sf::Vector2f cohesion = Cohesion().direction;
	sf::Vector2f separation = Separation().direction;

	alignment *= alignmentWeight;
	cohesion *= cohesionWeight;
	separation *= separationWeight;

	steering.direction += alignment;
	steering.direction += cohesion;
	steering.direction += separation;

	return steering;
}

void FlockBehavior::SetTarget(sf::Vector2f target)
{
	this->target = target;
}

Boid* FlockBehavior::GetFlockLeader() const
{
	for (Boid* boid : this->flock)
	{
		if (boid->isFlockLeader)
		{
			return boid;
		}
	}

	return nullptr;
}

SteeringOutput FlockBehavior::Alignment()
{
	SteeringOutput steering;

	Boid* flockLeader = this->GetFlockLeader();

	if (flockLeader)
	{
		this->SetTarget(flockLeader->position);
	}

	if (SeekBehavior* seekComponent = this->GetOwner().GetComponent<SeekBehavior>())
	{
		return seekComponent->GetSteering();
	}
	else
	{
		std::cout << "(FlockBehavior) Alignment: could not find Seek component!" << std::endl;
	}

	return steering;
}

SteeringOutput FlockBehavior::Cohesion()
{
	return SteeringOutput();
}

SteeringOutput FlockBehavior::Separation()
{
	return SteeringOutput();
}
