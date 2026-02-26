#pragma once

class GameObject;

class Component
{
public:
	virtual void Update(float deltaTime) {};

	void SetOwner(GameObject* newOwner);
	GameObject& GetOwner() const;

private:
	GameObject* owner = nullptr;
};