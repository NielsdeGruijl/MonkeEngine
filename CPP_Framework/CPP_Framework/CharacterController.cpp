#include "CharacterController.h"

#include <iostream>

CharacterController::CharacterController(GameObject* owner)
	: gameObject(owner)
{
}

CharacterController::~CharacterController()
{
}

void CharacterController::Move(Vector2 velocity)
{
	gameObject->SetPosition(gameObject->position + velocity);
}

// Figure out a way to pass the pawn class to the character controller rather than the GameObject class.

// Possibly figure out a way to move the "owner" without having to fetch their position first or needing a special "move" method on the owner class