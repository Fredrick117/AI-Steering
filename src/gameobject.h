#pragma once

#include <SFML/Graphics.hpp>

class Component;

class GameObject
{
public:
	GameObject(sf::Vector2f goPosition = { 0.0f, 0.0f }, sf::Vector2f goRotation = { 0.0f, 0.0f } );
	~GameObject();

	sf::Vector2f position;
	sf::Vector2f rotation;

	std::vector<Component*> components;

	virtual void Update(float deltaTime);

	void AddComponent(Component* component);
	
	template<typename T>
	T* GetComponent()
	{
		for (Component* c : this->components)
		{
			T* target = dynamic_cast<T*>(c);
			if (target != nullptr)
			{
				return target;
			}
		}

		return nullptr;
	}
};