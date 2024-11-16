#include <iostream>

#include "../Objects/Pawn.h"
#include "CharacterController.h"

extern const int unitSize;
extern float deltaTime;

CharacterController::CharacterController(float pDrag, float pGravity, float pFriction, float pBounciness)
	: Component()
{
	drag = pDrag;
	gravity = pGravity;
	friction = pFriction;
	bounciness = pBounciness;
}

CharacterController::~CharacterController()
{
}

void CharacterController::OnLoad()
{
	Component::OnLoad();

	if (collider == nullptr)
		collider = object->AddComponent<AABBCollider>(object->GetSize(), object->position);
}
	
void CharacterController::Update()
{
	Component::Update();

	if (gravity > 0)
		ApplyGravity();

	if (velocity.GetLength() > 0)
		Move();
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

	ApplyDrag();
}

void CharacterController::HandleCollision(Collision collision)
{
	if (!collider->isTrigger)
	{
		if (bounciness > 0)
		{
			Vector2 tVelocity;

			if (abs(collision.normal.x) > 0)
				tVelocity = Vector2(abs(velocity.x) * collision.normal.x, velocity.y);
			if (abs(collision.normal.y) > 0)
				tVelocity = Vector2(velocity.x, abs(velocity.y) * collision.normal.y);

			velocity = tVelocity * bounciness;
			return;
		}

		Vector2 newPos = object->position + velocity * collision.entryTime;
		object->SetPosition(newPos);

		float dotProduct = (velocity.x * collision.normal.y + velocity.y * collision.normal.x) * collision.remainingTime;
		velocity = Vector2(dotProduct * collision.normal.y, dotProduct * collision.normal.x);
		
		if (friction > 0)
		{
			float tFriction = (velocity.GetLength() * velocity.GetLength()) * friction;
			Vector2 frictionVector = velocity.normalized * tFriction * deltaTime;
			velocity -= frictionVector;
		}
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