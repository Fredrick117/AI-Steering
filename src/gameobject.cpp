#include "gameobject.h"
#include "component.h"

GameObject::GameObject(sf::Vector2f goPosition, sf::Vector2f goRotation) 
	: position(goPosition), rotation(goRotation) {}

GameObject::~GameObject()
{
	for (Component* component : this->components)
	{
		delete component;
	}
}

void GameObject::Update(float deltaTime)
{
	for (Component* component : this->components)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Draw()
{

}

void GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	this->components.push_back(component);
}
