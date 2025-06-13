#include "Game.h"
#include "../Math/Timer.h"
#include "../../Testing/TestData.h"

extern const int unitSize = 100;
float deltaTime;
float fixedDeltaTime = 0.02f;
float accumulator;

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
	fpsCounterText.setPosition(renderWindow.getSize().x - 100, 10);

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
	sf::Clock gameTime;

	//renderWindow.setFramerateLimit(144);
	renderWindow.setVerticalSyncEnabled(false);
	while (renderWindow.isOpen())
	{
		if (gameTime.getElapsedTime().asSeconds() > 30)
			renderWindow.close();

		testData.AddData(timeClock.restart().asMicroseconds());

		while (renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				renderWindow.close();
		}

		deltaTime = clock.restart().asSeconds();

		fps++;
		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			//int averageFps = (int)fps / fpsClock.getElapsedTime().asSeconds();
			std::string fpsCount = std::to_string((int)fps);
			fpsCounterText.setString(sf::String(fpsCount.c_str()));
			fps = 0;
			fpsClock.restart();
		}

		renderWindow.clear();

		if (Scene* scene = sceneManager.GetCurrentScene())
		{
			scene->CleanUpObjects();
			
			int fixedUpdateCalls = 0;
			accumulator += deltaTime;
			while (accumulator >= fixedDeltaTime)
			{
				scene->FixedUpdate();
				accumulator -= fixedDeltaTime;
				fixedUpdateCalls++;
			}

			scene->Update();
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