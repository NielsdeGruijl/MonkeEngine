#include "InputHandler.h"

#include <iostream>

bool InputHandler::GetKey(std::string inputActionName)
{
	if (currentInputActionMap == nullptr)
	{
		std::cout << "InputHandler doesn't have an input action map. \n";
		return false;
	}

	if (sf::Keyboard::isKeyPressed(currentInputActionMap->GetKeyBind(inputActionName)))
		return true;

	return false;
}

bool InputHandler::GetKeyDown(std::string inputActionName)
{
	if (currentInputActionMap == nullptr)
	{
		std::cout << "InputHandler doesn't have an input action map. \n";
		return false;
	}

	InputAction* inputAction = currentInputActionMap->GetInputAction(inputActionName);

	if (!inputAction->previousFrameActive && sf::Keyboard::isKeyPressed(inputAction->keybind))
	{
		inputAction->currentFrameActive = true;
		return true;
	}

	return false;
}

bool InputHandler::GetKeyUp(std::string inputActionName)
{
	if (currentInputActionMap == nullptr)
	{
		std::cout << "InputHandler doesn't have an input action map. \n";
		return false;
	}

	InputAction* inputAction = currentInputActionMap->GetInputAction(inputActionName);

	if (inputAction->previousFrameActive && !sf::Keyboard::isKeyPressed(inputAction->keybind))
	{
		inputAction->currentFrameActive = false;
		return true;
	}

	return false;
}

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

void InputHandler::ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey)
{
	currentInputActionMap->ChangeKey(inputActionName, newKey);
}

void InputHandler::SetInputActionMap(InputActionMap* playerInputActionMap)
{
	currentInputActionMap = playerInputActionMap;
}