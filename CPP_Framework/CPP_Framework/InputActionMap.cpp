#include "InputActionMap.h"

#include <iostream>

InputActionMap::InputActionMap()
{
	using sf::Keyboard;

	inputActions["forward"] = InputAction(Keyboard::W);
	inputActions["backward"] = InputAction(Keyboard::S);
	inputActions["left"] = InputAction(Keyboard::A);
	inputActions["right"] = InputAction(Keyboard::D);

	inputActions["interact"] = InputAction(Keyboard::F);

	inputActions["test"] = InputAction(Keyboard::T);

	InitializeKeybindsMap();
}

InputActionMap::~InputActionMap()
{
}

void InputActionMap::ChangeKey(std::string inputActionName, InputAction newInputAction)
{
	if (inputActions.find(inputActionName) != inputActions.end())
		std::cout << "Input action \"" << inputActionName << "\" has been remapped to " << newInputAction.keybind << "\n";
	else
		std::cout << "Input action \"" << inputActionName << "\" has been added and mapped to " << newInputAction.keybind << "\n";

	inputActions[inputActionName] = newInputAction;
}

void InputActionMap::UpdateKeyStatus()
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed(keys[i]->keybind))
		{
			keys[i]->previousFrameActive = keys[i]->currentFrameActive;
			keys[i]->currentFrameActive = true;
		}
		else
		{
			keys[i]->previousFrameActive = keys[i]->currentFrameActive;
			keys[i]->currentFrameActive = false;
		}
	}
}

void InputActionMap::InitializeKeybindsMap()
{
	for (auto& kv : inputActions)
	{
		InputAction* action = &kv.second;

		keys.push_back(action);
	}
}

sf::Keyboard::Key InputActionMap::GetKeyBind(std::string inputActionName) const
{
	if (inputActions.find(inputActionName) != inputActions.end())
		return inputActions.at(inputActionName).keybind;

	std::cout << "Input action \"" << inputActionName << "\" does not exist.\n";

	return sf::Keyboard::Unknown;
}

InputAction* InputActionMap::GetInputAction(std::string inputActionName)
{
	InputAction* inputAction;
	if (inputActions.find(inputActionName) != inputActions.end())
		return &inputActions.at(inputActionName);

	std::cout << "Input action \"" << inputActionName << "\" does not exist.\n";

	// returns default input action with sf::Keyboard::Unknown
	return nullptr; 
}