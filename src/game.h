#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <imgui.h>
#include <imgui-SFML.h>
#include <random>

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
		newBoid->AddComponent(new Renderable(newBoid, "img/Boid.png"));
		
		int randomX = spawnBuffer + (rand() % window.getSize().x - spawnBuffer);
		int randomY = spawnBuffer + (rand() % window.getSize().y - spawnBuffer);

		newBoid->position = { static_cast<float>(randomX), static_cast<float>(randomY) };

		gameObjects.push_back(newBoid);
	}

	sf::RenderWindow window;

	std::vector<GameObject*> gameObjects;

	std::array<const char*, 3> behaviorTypes;

	int numBoids = 0;

	int spawnBuffer = 25;
};