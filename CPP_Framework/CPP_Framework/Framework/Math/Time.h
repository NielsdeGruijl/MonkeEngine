#pragma once

#include <SFML/Graphics.hpp>


class Time {

public:
	float deltaTime;

public:
	void CalculateDeltaTime()
	{
		currentFrameTime = clock.getElapsedTime().asSeconds();

		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		std::cout << "deltaTime: " << deltaTime << "\n";
	}

	void GetDeltaTime()
	{
		float time = deltaClock.restart().asSeconds();

		std::cout << "DeltaClock: " << time << "\n";
	}

private:
	sf::Clock clock;
	sf::Clock deltaClock;
	float currentFrameTime;
	float lastFrameTime;
};