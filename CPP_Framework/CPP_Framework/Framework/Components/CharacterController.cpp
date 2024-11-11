#include "CharacterController.h"
#include "../Math/Time.h"

#include <iostream>

extern const int unitSize;
extern float deltaTime;

CharacterController::CharacterController(GameObject* pOwner)
	: owner(pOwner)
{
	drag = 1;
	gravity = 1;
	useGravity = true;
}

CharacterController::~CharacterController()
{
}

void CharacterController::Move()
{
	owner->SetPosition(owner->position + velocity * deltaTime);
}

void CharacterController::SetVelocity(Vector2 pVelocity)
{
	velocity = pVelocity;
}

void CharacterController::AddVelocity(Vector2 pVelocity, VelocityType pVelocityType)
{
	switch (pVelocityType)
	{
	case CharacterController::continuous:
		velocity += ((pVelocity) * (float)unitSize) * deltaTime;
		break;
	case CharacterController::instant:
		velocity += pVelocity * (float)unitSize;
		break;
	}
}

void CharacterController::ApplyDrag()
{
	float tDrag = velocity.GetLength() * drag;
	Vector2 dragVector = (velocity.normalized) * tDrag * deltaTime;

	velocity -= dragVector;

	if (velocity.GetLength() <= 0.001f)
		velocity = Vector2(0, 0);
}

void CharacterController::ApplyGravity()
{
	velocity += Vector2(0, gravity);
}

void CharacterController::Update()
{
	if (useGravity && velocity.y != 0)
		ApplyGravity();

	if (velocity.GetLength() > 0)
	{
		ApplyDrag();
		Move();

		//std::cout << velocity.GetLength() << "\n";
	}
}

// Figure out a way to pass the pawn class to the character controller rather than the GameObject class.

// Possibly figure out a way to move the "owner" without having to fetch their position first or needing a special "move" method on the owner class