#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
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

	sf::RenderWindow window;

	std::vector<GameObject*> gameObjects;

	// TODO: currently applies to all boids, only apply to selected ones in the future?
	bool seekEnabled = true;
	bool fleeEnabled = false;

	int numBoids = 0;
};