#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Timer {

public:
	~Timer()
	{
		std::cout << clock.restart().asMicroseconds() << "us\n";
		//std::cout << clock.restart().asMilliseconds() << "ms\n";
	}
private:
	sf::Clock clock;
};