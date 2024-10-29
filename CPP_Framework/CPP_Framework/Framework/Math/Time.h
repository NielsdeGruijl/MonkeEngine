#pragma once

#include <SFML/Graphics.hpp>


class Time {

public:
	float deltaTime;
public:
	void CalculateDeltaTime()
	{
		currentFrameTime = clock.getElapsedTime();

		deltaTime = currentFrameTime.asSeconds() - lastFrameTime;
		lastFrameTime = currentFrameTime.asSeconds();
	}

private:
	sf::Clock clock;
	sf::Time currentFrameTime;
	float lastFrameTime;
};