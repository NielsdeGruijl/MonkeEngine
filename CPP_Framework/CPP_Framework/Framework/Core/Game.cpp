#include "Game.h"
#include "../Math/Timer.h"
#include "../../Testing/TestData.h"

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
	TestData testData;

	fpsClock.restart();

	sf::Clock timeClock;

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
		if (fpsClock.getElapsedTime().asSeconds() > .1f)
		{
			int averageFps = (int)fps / fpsClock.getElapsedTime().asSeconds();
			std::string fpsCount = std::to_string(averageFps);
			fpsCounterText.setString(sf::String(fpsCount.c_str()));
			fps = 0;
			fpsClock.restart();
		}

		testData.AddData(timeClock.restart().asMilliseconds());

		renderWindow.clear();

		if (Scene* scene = sceneManager.GetCurrentScene())
		{
			scene->CleanUpObjects();
			scene->UpdateScene();
			scene->RenderScene(&renderWindow);
		}

		renderWindow.draw(fpsCounterText);

		renderWindow.display();
	}
}

void Game::AddScene(std::string sceneName, Scene* scene)
{
	sceneManager.AddScene(sceneName, scene);
}