#include "game.h"

#include <imgui.h>
#include <imgui-SFML.h>

Game::Game()
{
	window = sf::RenderWindow(sf::VideoMode({ 800, 800 }), "Boids-A-Million");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);	// TODO: cassert
}

Game::~Game()
{
	for (auto& gameObject : gameObjects)
	{
		delete gameObject;
	}

	ImGui::SFML::Shutdown();
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
		CreateBoidDebugMenu();
		Draw();
	}
}

void Game::Update(float deltaTime)
{
	ImGui::SFML::Update(window, sf::seconds(deltaTime));

	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Game::HandleInput()
{
	while (const auto event = window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(window, *event);

		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
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
				ImGuiIO& io = ImGui::GetIO();
				if (io.WantCaptureMouse)
				{
					io.AddMouseButtonEvent(0, true);
					continue;
				}

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

	ImGui::SFML::Render(window);

	window.display();
}

void Game::CreateBoidDebugMenu()
{
	ImGui::Begin("AI Movement Behaviors");
	ImGui::BeginChild("Basic Steering");
	ImGui::Checkbox("Seek", &this->checkbox1);
	ImGui::Checkbox("Arrive", &this->checkbox2);
	ImGui::SliderInt("Number of boids", &numBoids, 0, 100);
	ImGui::EndChild();
	ImGui::End();
}
