#include <iostream>

#include "../Math/Time.h"
#include "../Objects/Pawn.h"
#include "CharacterController.h"

extern const int unitSize;
extern float deltaTime;

CharacterController::CharacterController(Pawn* pawn, float pDrag, float pGravity, float pFriction)
	: Component()
{
	drag = pDrag;
	gravity = pGravity;
	friction = pFriction;
}

CharacterController::~CharacterController()
{
}

void CharacterController::Update()
{
	Component::Update();

	if (gravity > 0)
		ApplyGravity();

	if (velocity.GetLength() > 0)
	{
		ApplyDrag();
		Move();
	}
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

void CharacterController::HandleCollision(Collision collision)
{
	if (!collider->isTrigger)
	{
		Vector2 newPos = object->position + velocity * collision.entryTime;
		object->SetPosition(newPos);

		float dotProduct = (velocity.x * collision.normal.y + velocity.y * collision.normal.x) * collision.remainingTime;
		velocity = Vector2(dotProduct * collision.normal.y, dotProduct * collision.normal.x);
	}
}

void CharacterController::Move()
{
	object->SetPosition(object->position + velocity * deltaTime);
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

// Figure out a way to pass the pawn class to the character controller rather than the GameObject class.

// Possibly figure out a way to move the "owner" without having to fetch their position first or needing a special "move" method on the owner class