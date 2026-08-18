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

#define DEFAULT_WIN_SIZE_X 1920
#define DEFAULT_WIN_SIZE_Y 1080

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

	void SpawnBoidAtRandomPosition()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distributionX(spawnBuffer, window.getSize().x - spawnBuffer);
		std::uniform_int_distribution<int> distributionY(spawnBuffer, window.getSize().y - spawnBuffer);

		int randomX = distributionX(gen);
		int randomY = distributionY(gen);
		sf::Vector2f spawnPosition = sf::Vector2f(randomX, randomY);
		
		gameObjects.push_back(std::make_shared<Boid>(spawnPosition));
	}

	sf::RenderWindow window;

	// TODO: move this data into an ECS architecture?
	std::vector<std::shared_ptr<GameObject>> gameObjects;

	int spawnBuffer = 25;
};