#include "game.h"

Game::Game()
{
	window = sf::RenderWindow(sf::VideoMode({ 800, 800 }), "Boids-A-Million");
	window.setFramerateLimit(30);
}

Game::~Game()
{
	for (auto& gameObject : gameObjects)
	{
		delete gameObject;
	}
}

void Game::Run()
{
	Boid* boid1 = new Boid();
	boid1->AddComponent(new Rigidbody(boid1));
	boid1->AddComponent(new Renderable(boid1, 10.0f));

	Rigidbody* rb = boid1->GetComponent<Rigidbody>();

	gameObjects.push_back(boid1);

	sf::Clock dtClock;
	while (window.isOpen())
	{
		HandleInput();
		Update(dtClock.restart().asSeconds());
		Draw();
	}
}

void Game::Update(float deltaTime)
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Game::HandleInput()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				std::cout << "escape" << std::endl;
			}
		}
		else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mousePressed->button == sf::Mouse::Button::Left)
			{
				for (auto& gameObject : gameObjects)
				{
					if (Boid* b = dynamic_cast<Boid*>(gameObject))
					{
						b->GetComponent<SeekBehavior>()->SetTarget(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->window)));
					}
				}
			}
		}
	}
}

void Game::Draw()
{
	window.clear();

	for (GameObject* g : gameObjects)
	{
		Renderable* renderable = g->GetComponent<Renderable>();
		if (renderable != nullptr)
		{
			renderable->Draw(window);
		}
	}

	window.display();
}
