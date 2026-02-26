#include "component.h"
#include <cassert>

void Component::SetOwner(GameObject* newOwner)
{
	this->owner = newOwner;
}

GameObject& Component::GetOwner() const
{
	assert(this->owner && "Component::GetOwner called before owner was set");
	return *this->owner;
}
