#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

struct InputAction
{
	sf::Keyboard::Key keybind;
	bool currentFrameActive;
	bool previousFrameActive;
	
	InputAction()
		: keybind(sf::Keyboard::Unknown), currentFrameActive(false), previousFrameActive(false) {};
	InputAction(sf::Keyboard::Key _keybind)
		: keybind(_keybind), currentFrameActive(false), previousFrameActive(false) {};
	~InputAction() {};
};

class InputActionMap
{
public:
	InputActionMap();
	~InputActionMap();

	void ChangeKey(std::string inputActionName, InputAction newInputAction);
	void AddKey(std::string inputActionName, InputAction newInputAction);
	void UpdateKeyStatus();
	void InitializeKeybindsList();

	sf::Keyboard::Key GetKeyBind(std::string inputActionName) const;
	InputAction* GetInputAction(std::string inputActionName);


private:
	std::unordered_map<std::string, InputAction> currentInputActionMap;
	std::vector<InputAction*> keys;
};