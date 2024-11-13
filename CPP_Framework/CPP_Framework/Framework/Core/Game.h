#pragma once

#include <SFML/Graphics.hpp>

#include "../../Testing/TestScene.h"
#include "../../Testing/Player.h"
#include "../Math/Time.h"
#include "SceneManager.h"

#include <sstream>
#include <string>

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

	sf::Clock clock;

	// fps counter
	sf::Clock fpsClock;
	float fps;
	sf::Text text;
	sf::Font font;
};