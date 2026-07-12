#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <imgui.h>
#include <imgui-SFML.h>
#include <random>
#include <memory>

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

	void CreateBoidDebugMenu(); // TODO: rename to "DrawBoidDebugMenu"
	void DrawFPSCounter();

	void SpawnBoid()
	{
		int randomX = spawnBuffer + (rand() % window.getSize().x - spawnBuffer);
		int randomY = spawnBuffer + (rand() % window.getSize().y - spawnBuffer);
		sf::Vector2f spawnPosition = sf::Vector2f(randomX, randomY);
		
		gameObjects.push_back(std::make_shared<Boid>(spawnPosition));
	}

	sf::RenderWindow window;

	// TODO: move this data into an ECS architecture?
	std::vector<std::shared_ptr<GameObject>> gameObjects;

	int spawnBuffer = 25;
};