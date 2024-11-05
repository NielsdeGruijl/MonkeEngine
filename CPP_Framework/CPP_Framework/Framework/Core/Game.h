#pragma once

#include <SFML/Graphics.hpp>

#include "../../Testing/TestScene.h"
#include "../../Testing/Player.h"
#include "../Math/Time.h"
#include "SceneManager.h"

class Game
{
public:
	Game(int horizontalResolution, int verticalResolution);
	~Game();

	void Run();
	void AddScene(std::string sceneName, Scene* scene);

private:
	sf::RenderWindow renderWindow;
	SceneManager sceneManager;

	int frames;

	float totalTimeElapsed;

	sf::Clock clock;
};