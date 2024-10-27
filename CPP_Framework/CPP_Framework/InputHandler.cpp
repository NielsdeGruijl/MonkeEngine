#include "InputHandler.h"

#include <iostream>

int InputHandler::GetVerticalAxis()
{
	if (GetKey("forward"))
		return -1;
	if (GetKey("backward"))
		return 1;

	return 0;
}

int InputHandler::GetHorizontalAxis()
{
	if (GetKey("left"))
		return -1;
	if (GetKey("right"))
		return 1;

	return 0;
}

bool InputHandler::GetKey(std::string inputActionName)
{
	if (sf::Keyboard::isKeyPressed(inputActions->GetKeyBind(inputActionName)))
		return true;

	return false;
}

bool InputHandler::GetKeyDown(std::string inputActionName)
{
	InputAction* inputAction = inputActions->GetInputAction(inputActionName);

	if (!inputAction->previousFrameActive && sf::Keyboard::isKeyPressed(inputAction->keybind))
		return true;

	return false;
}

bool InputHandler::GetKeyUp(std::string inputActionName)
{
	InputAction* inputAction = inputActions->GetInputAction(inputActionName);

	if (inputAction->previousFrameActive && !sf::Keyboard::isKeyPressed(inputAction->keybind))
		return true;

	return false;
}

void InputHandler::ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey)
{
	inputActions->ChangeKey(inputActionName, newKey);
}