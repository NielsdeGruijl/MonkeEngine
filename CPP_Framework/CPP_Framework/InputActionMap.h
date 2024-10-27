#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

struct InputAction
{
	sf::Keyboard::Key keybind;
	bool isPressed;

	InputAction(sf::Keyboard::Key _keybind);
};

class InputActionMap
{
public:
	InputActionMap();
	~InputActionMap();

	void ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey);
	sf::Keyboard::Key GetKey(std::string inputActionName) const;


private:
	std::unordered_map<std::string, sf::Keyboard::Key> inputActions;
};