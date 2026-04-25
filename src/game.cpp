#include "game.h"

Game::Game()
{
	window = sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Boids-A-Million");
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
						b->GetCurrentSteeringBehavior()->SetTarget(
							static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->window)));
					}
				}
			}
			else if (mousePressed->button == sf::Mouse::Button::Middle)
			{
				Utils::SpawnBoidAtMousePosition(this->window, gameObjects);
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

		ShapeRenderable* shapeRenderable = g->GetComponent<ShapeRenderable>();
		if (shapeRenderable != nullptr)
		{
			shapeRenderable->Draw(window);
		}

		Boid* b = dynamic_cast<Boid*>(g);
		if (b != nullptr)
		{
			if (b->debugEnabled)
				b->DrawDebug(window);
		}
	}

	ImGui::SFML::Render(window);

	window.display();
}

void Game::CreateBoidDebugMenu()
{
	ImGui::Begin("AI Movement Behaviors");

	if (ImGui::Button("Add boid", { 70, 20 }))
	{
		SpawnBoid();
	}

	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Boids");
	ImGui::BeginChild("Scrolling");

	for (int i = 0; i < gameObjects.size(); i++)
	{
		Boid* boid = dynamic_cast<Boid*>(gameObjects[i]);
		if (boid == nullptr)
			return;

		ImGui::Text("Boid %02d", i + 1);
		ImGui::SameLine();

		/*if (ImGui::SmallButton("Delete"))
		{
			std::cout << "begone!" << std::endl;
		}
		ImGui::SameLine();*/

		std::string boidIdentifier = "##boid" + std::to_string(i);

		auto names = boid->GetBehaviorNames();
		if (ImGui::Combo(boidIdentifier.c_str(), &boid->currentBehavior, names.data(), static_cast<int>(names.size())))
		{
			boid->SetCurrentSteeringBehavior(boid->currentBehavior);
		}
		
		ImGui::Indent();
		ImGui::PushID(i);
		ImGui::Checkbox("Show direction?", &boid->debugEnabled);
		ImGui::PopID();
		ImGui::Unindent();
	}

	ImGui::EndChild();

	ImGui::End();
}
