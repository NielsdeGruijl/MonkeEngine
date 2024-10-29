#include "InputActionMap.h"

#include <iostream>

InputActionMap::InputActionMap()
{
	using sf::Keyboard;

	currentInputActionMap["forward"] = InputAction(Keyboard::W);
	currentInputActionMap["backward"] = InputAction(Keyboard::S);
	currentInputActionMap["left"] = InputAction(Keyboard::A);
	currentInputActionMap["right"] = InputAction(Keyboard::D);

	currentInputActionMap["interact"] = InputAction(Keyboard::F);

	currentInputActionMap["test"] = InputAction(Keyboard::T);

	InitializeKeybindsMap();
}

InputActionMap::~InputActionMap()
{
}

void InputActionMap::ChangeKey(std::string inputActionName, InputAction newInputAction)
{
	if (currentInputActionMap.find(inputActionName) != currentInputActionMap.end())
		std::cout << "Input action \"" << inputActionName << "\" has been remapped to " << newInputAction.keybind << "\n";
	else
		std::cout << "Input action \"" << inputActionName << "\" has been added and mapped to " << newInputAction.keybind << "\n";

	currentInputActionMap[inputActionName] = newInputAction;
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

		if (keys[i]->keybind == sf::Keyboard::T)
		{
			//std::cout << keys[i]->previousFrameActive;
		}
	}
}

void InputActionMap::InitializeKeybindsMap()
{
	for (auto& kv : currentInputActionMap)
	{
		InputAction* action = &kv.second;

		keys.push_back(action);
	}
}

sf::Keyboard::Key InputActionMap::GetKeyBind(std::string inputActionName) const
{
	if (currentInputActionMap.find(inputActionName) != currentInputActionMap.end())
		return currentInputActionMap.at(inputActionName).keybind;

	std::cout << "Input action \"" << inputActionName << "\" does not exist.\n";

	return sf::Keyboard::Unknown;
}

InputAction* InputActionMap::GetInputAction(std::string inputActionName)
{
	InputAction* inputAction;
	if (currentInputActionMap.find(inputActionName) != currentInputActionMap.end())
		return &currentInputActionMap.at(inputActionName);

	std::cout << "Input action \"" << inputActionName << "\" does not exist.\n";

	// returns default input action with sf::Keyboard::Unknown
	return nullptr; 
}