#include "Game.h"

extern const int unitSize = 100;
Time _time;

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

	while (renderWindow.isOpen())
	{
		_time.CalculateDeltaTime();

		while (renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				renderWindow.close();
		}

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