#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "InputActionMap.h"
#include "Vector2.h"

class InputHandler
{
public:
	int GetVerticalAxis();
	int GetHorizontalAxis();

	bool GetKey(std::string inputActionName);
	bool GetKeyDown(std::string inputActionName);
	bool GetKeyUp(std::string inputActionName);

	void ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey);

	InputActionMap* inputActions;


private:
};