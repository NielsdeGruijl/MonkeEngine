#include "InputHandler.h"

int InputHandler::GetVerticalAxis()
{
	using sf::Keyboard;

	if (Keyboard::isKeyPressed(inputActions.GetKey("forward")))
		return -1;
	if (Keyboard::isKeyPressed(inputActions.GetKey("backward")))
		return 1;

	return 0;
}

int InputHandler::GetHorizontalAxis()
{
	using sf::Keyboard;

	if (Keyboard::isKeyPressed(inputActions.GetKey("left")))
		return -1;
	if (Keyboard::isKeyPressed(inputActions.GetKey("right")))
		return 1;

	return 0;
}

bool InputHandler::GetKeyPressed(std::string inputActionName)
{
	using sf::Keyboard;

	if(Keyboard::isKeyPressed(inputActions.GetKey(inputActionName)))
		return true;

	return false;
}

bool InputHandler::GetKeyDown(std::string inputActionName)
{

}

bool InputHandler::GetKeyUp(std::string inputActionName)
{

}

void InputHandler::ChangeKey(std::string inputActionName, sf::Keyboard::Key newKey)
{
	inputActions.ChangeKey(inputActionName, newKey);
}