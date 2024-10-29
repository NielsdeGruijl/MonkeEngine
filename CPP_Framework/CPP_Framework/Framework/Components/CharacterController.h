#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Objects/GameObject.h"

class CharacterController
{
public:
	CharacterController(GameObject* owner);
	~CharacterController();

	Vector2 velocity;

public:
	void Move(Vector2 velocity);

private:
	GameObject* gameObject;

private:

};