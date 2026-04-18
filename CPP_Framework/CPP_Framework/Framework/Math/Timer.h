#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Timer {

public:
	Timer(std::string name)
		: name(name)
	{
	}

	Timer()
		: name("")
	{
	}

	~Timer()
	{
		std::cout << clock.restart().asMicroseconds() << "us " << name << std::endl;
		//std::cout << clock.restart().asMilliseconds() << "ms\n";
	}
private:
	sf::Clock clock;
	std::string name;
};