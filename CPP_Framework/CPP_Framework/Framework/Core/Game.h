#pragma once

#include <SFML/Graphics.hpp>

#include "../../Testing/TestScene.h"
#include "../../Testing/Player.h"
#include "../Math/Time.h"

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
};