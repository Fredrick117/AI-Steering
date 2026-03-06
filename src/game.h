#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <imgui.h>
#include <imgui-SFML.h>

#include "boid/boid.h"
#include "gameobject.h"
#include "components/component.h"
#include "components/renderable.h"
#include "components/rigidbody.h"
#include "steering/flee.h"
#include "steering/seek.h"
#include "utilities.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
	void Update(float deltaTime);
	void HandleInput();
	void Draw();

	void CreateBoidDebugMenu();

	void SpawnBoid()
	{
		Boid* newBoid = new Boid();
		newBoid->AddComponent(new Rigidbody(newBoid));
		newBoid->AddComponent(new Renderable(newBoid, 10.0f));

		gameObjects.push_back(newBoid);
	}

	sf::RenderWindow window;

	std::vector<GameObject*> gameObjects;

	std::array<const char*, 2> behaviorTypes;

	int numBoids = 0;
};