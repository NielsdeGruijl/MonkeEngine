#include "InputActionMap.h"

#include <iostream>

InputAction::InputAction(sf::Keyboard::Key _keybind)
	: keybind(_keybind), isPressed(false)
{
}

InputActionMap::InputActionMap()
{
	using sf::Keyboard;

	inputActions["forward"] = Keyboard::W;
	inputActions["backward"] = Keyboard::S;
	inputActions["left"] = Keyboard::A;
	inputActions["right"] = Keyboard::D;

	inputActions["interact"] = Keyboard::F;
}

InputActionMap::~InputActionMap()
{
}

void InputActionMap::ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey)
{
	if (inputActions.find(inputActionName) != inputActions.end())
		std::cout << "Input action \"" << inputActionName << "\" has been remapped to " << newKey << "\n";
	else
		std::cout << "Input action \"" << inputActionName << "\" has been added and mapped to " << newKey << "\n";

	inputActions[inputActionName] = newKey;
}

sf::Keyboard::Key InputActionMap::GetKey(std::string inputActionName) const
{
	if (inputActions.find(inputActionName) != inputActions.end())
		return inputActions.at(inputActionName);

	std::cout << "Input action \"" << inputActionName << "\" does not exist.\n";

	return sf::Keyboard::Unknown;
}