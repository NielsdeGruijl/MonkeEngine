#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"
#include "GameObject.h"

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