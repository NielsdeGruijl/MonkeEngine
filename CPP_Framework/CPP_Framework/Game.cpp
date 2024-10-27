#include "Game.h"

extern const int unitSize = 100;
Time _time;

Game::Game()
	: renderWindow(sf::VideoMode(1280, 720), "CPP_Framework"), currentScene(nullptr)
{
}

Game::~Game()
{
}

void Game::Run()
{
	sf::Event event;

	TestScene testScene;

	Player player("Player", "Cat.jpg", 236);
	player.SetPosition(Vector2(0, 0));
	player.SetOrigin(Vector2(0.5f, 0.5f));

	player.SetActionMap(&inputActionMap);

	testScene.AddObject(player);

	currentScene = &testScene;

	renderWindow.setFramerateLimit(60);
	while (renderWindow.isOpen())
	{
		_time.CalculateDeltaTime();

		while (renderWindow.pollEvent(event))
		{
			HandleEvents(event);
		}

		renderWindow.clear();

		currentScene->RenderScene(&renderWindow);
		currentScene->UpdateScene();

		renderWindow.display();

		inputActionMap.UpdateKeyStatus();
	}
}

void Game::HandleEvents(sf::Event _event)
{
	switch (_event.type)
	{
		case sf::Event::Closed:
			renderWindow.close();
			break;
	}
}