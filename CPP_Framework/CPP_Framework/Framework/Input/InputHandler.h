#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "../Math/Vector2.h"
#include "InputActionMap.h"

class InputHandler
{
public:
	bool GetKey(std::string inputActionName);
	bool GetKeyDown(std::string inputActionName);
	bool GetKeyUp(std::string inputActionName);

	int GetVerticalAxis();
	int GetHorizontalAxis();

	void ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey);
	void SetInputActionMap(InputActionMap* inputActonMap);

private:
	InputActionMap* currentInputActionMap;
};
