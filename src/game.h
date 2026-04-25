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
#include "components/shape_renderable.h"
#include "components/rigidbody.h"
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
		int randomX = spawnBuffer + (rand() % window.getSize().x - spawnBuffer);
		int randomY = spawnBuffer + (rand() % window.getSize().y - spawnBuffer);
		
		Boid* newBoid = new Boid({ static_cast<float>(randomX), static_cast<float>(randomY) });
		
		gameObjects.push_back(newBoid);
	}

	sf::RenderWindow window;

	std::vector<GameObject*> gameObjects;

	int numBoids = 0;

	int spawnBuffer = 25;
};