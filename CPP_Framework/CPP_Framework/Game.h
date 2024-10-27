#pragma once

#include <SFML/Graphics.hpp>

#include "TestScene.h"
#include "Time.h"
#include "Player.h"

#include "InputActionMap.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
	void HandleEvents(sf::Event event);

private:
	sf::RenderWindow renderWindow;
	Scene* currentScene;

	InputActionMap inputActionMap;
};