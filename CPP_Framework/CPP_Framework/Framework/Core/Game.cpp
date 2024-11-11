#include "Game.h"

extern const int unitSize = 100;
float deltaTime;

Game::Game(int horizontalResolution, int verticalResolution)
	: renderWindow(sf::VideoMode(horizontalResolution, verticalResolution), "CPP_Framework")
{
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

		renderWindow.clear();

		if (sceneManager.GetCurrentScene() != nullptr)
		{
			sceneManager.GetCurrentScene()->UpdateScene();
			sceneManager.GetCurrentScene()->RenderScene(&renderWindow);
		}

		renderWindow.display();
	}
}

void Game::AddScene(std::string sceneName, Scene* scene)
{
	sceneManager.AddScene(sceneName, scene);
}