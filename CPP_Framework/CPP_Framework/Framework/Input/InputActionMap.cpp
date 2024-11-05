#include "InputActionMap.h"

#include <iostream>

InputActionMap::InputActionMap()
{
	using sf::Keyboard;

	currentInputActionMap["forward"] = InputAction(Keyboard::W);
	currentInputActionMap["backward"] = InputAction(Keyboard::S);
	currentInputActionMap["left"] = InputAction(Keyboard::A);
	currentInputActionMap["right"] = InputAction(Keyboard::D);

	currentInputActionMap["dash"] = InputAction(Keyboard::Space);

	currentInputActionMap["test"] = InputAction(Keyboard::T);

	InitializeKeybindsList();
}

InputActionMap::~InputActionMap()
{
}

void InputActionMap::ChangeKey(std::string inputActionName, InputAction newInputAction)
{
	if (currentInputActionMap.find(inputActionName) != currentInputActionMap.end())
		currentInputActionMap[inputActionName] = newInputAction;
	else
		std::cout << "Input action with name \"" << inputActionName << "\" doesn't exist, use AddKey() instead. \n";
}

void InputActionMap::AddKey(std::string inputActionName, InputAction newInputAction)
{
	if (currentInputActionMap.find(inputActionName) == currentInputActionMap.end())
		currentInputActionMap[inputActionName] = newInputAction;
	else
		std::cout << "Input action with name \"" << inputActionName << "\" already exists, use ChangeKey() instead. \n";
}

void InputActionMap::UpdateKeyStatus()
{
	for (size_t i = 0; i < keys.size(); i++)
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

void InputActionMap::InitializeKeybindsList()
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