#include "Game.h"
#include "../Math/Timer.h"

extern const int unitSize = 100;
float deltaTime;

Game::Game(int horizontalResolution, int verticalResolution)
	: renderWindow(sf::VideoMode(horizontalResolution, verticalResolution), "CPP_Framework")
{
	fps = 0;

	if (!font.loadFromFile("Assets/Arial.ttf"))
	{
		std::cout << "Couldn't load font!";
	}

	fpsCounterText.setFont(font);
	fpsCounterText.setFillColor(sf::Color::White);
	fpsCounterText.setPosition(1190, 10);
}

Game::~Game()
{
}

void Game::Run()
{
	sf::Event event;

	renderWindow.setFramerateLimit(360);
	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				renderWindow.close();
		}

		deltaTime = clock.restart().asSeconds();

		fps++;
		std::string fpsCount = std::to_string((int)(fps / fpsClock.getElapsedTime().asSeconds()));
		//std::string fpsCount = std::to_string((int)(1 / deltaTime));
		fpsCounterText.setString(sf::String(fpsCount.c_str()));

		renderWindow.clear();

		if (sceneManager.GetCurrentScene() != nullptr)
		{
			sceneManager.GetCurrentScene()->CollisionUpdate();
			sceneManager.GetCurrentScene()->CleanUpObjects();
			sceneManager.GetCurrentScene()->UpdateScene();
			sceneManager.GetCurrentScene()->RenderScene(&renderWindow);
		}

		renderWindow.draw(fpsCounterText);

		renderWindow.display();
	}
}

void Game::AddScene(std::string sceneName, Scene* scene)
{
	sceneManager.AddScene(sceneName, scene);
}