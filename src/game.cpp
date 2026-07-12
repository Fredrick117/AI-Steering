#include "game.h"

Game::Game()
{
	window = sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "Boids-A-Million");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);	// TODO: cassert

}

Game::~Game()
{
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
		DrawFPSCounter();
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

				for (const auto& gameObject : gameObjects)
				{
					std::shared_ptr<Boid> boid = std::dynamic_pointer_cast<Boid>(gameObject);
					if (boid != nullptr)
					{
						boid->GetCurrentSteeringBehavior()->SetTarget(
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

	for (const auto& gameObject : gameObjects)
	{
		Renderable* renderable = gameObject->GetComponent<Renderable>();
		if (renderable != nullptr)
		{
			renderable->Draw(window);
		}

		ShapeRenderable* shapeRenderable = gameObject->GetComponent<ShapeRenderable>();
		if (shapeRenderable != nullptr)
		{
			shapeRenderable->Draw(window);
		}

		std::shared_ptr<Boid> boid = std::dynamic_pointer_cast<Boid>(gameObject);
		if (boid != nullptr && boid->debugEnabled)
		{
			boid->DrawDebug(window);
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

	int boidCounter = 1;
	for (const auto& gameObject : gameObjects)
	{
		std::shared_ptr<Boid> boid = std::dynamic_pointer_cast<Boid>(gameObject);
		if (boid == nullptr)
			continue;

		ImGui::Text("Boid %02d", boidCounter + 1);
		ImGui::SameLine();

		/*if (ImGui::SmallButton("Delete"))
		{
			std::cout << "begone!" << std::endl;
		}
		ImGui::SameLine();*/

		std::string boidIdentifier = "##boid" + std::to_string(boidCounter);

		auto names = boid->GetBehaviorNames();
		if (ImGui::Combo(boidIdentifier.c_str(), &boid->currentBehavior, names.data(), static_cast<int>(names.size())))
		{
			boid->SetCurrentSteeringBehavior(boid->currentBehavior);
		}
		
		ImGui::Indent();
		ImGui::PushID(boidCounter);
		ImGui::Checkbox("Show direction?", &boid->debugEnabled);
		ImGui::PopID();
		ImGui::Unindent();
	}

	ImGui::EndChild();

	ImGui::End();
}

void Game::DrawFPSCounter()
{
	ImGui::Begin("FPS");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}
