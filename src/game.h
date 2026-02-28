#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "boid/boid.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "renderable.h"

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

	sf::RenderWindow window;

	std::vector<GameObject*> gameObjects;

	bool checkbox1 = true;
	bool checkbox2 = false;

	int numBoids = 0;
};