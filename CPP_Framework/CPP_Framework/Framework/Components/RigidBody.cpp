#include <iostream>

#include "../Objects/Pawn.h"
#include "RigidBody.h"

#include "../Collisions/Collision.h"

extern const int unitSize;
extern float deltaTime;

RigidBody::RigidBody(float pDrag, float pGravity, float pFriction, float pBounciness)
	: Component()
{
	drag = pDrag;
	gravity = pGravity;
	friction = pFriction;
	bounciness = pBounciness;
}

RigidBody::~RigidBody()
{
}

void RigidBody::OnLoad()
{
	Component::OnLoad();

	if (collider == nullptr)
		collider = object->AddComponent<AABBCollider>(object->GetSize(), object->position);
}
	
void RigidBody::Update()
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

void RigidBody::SetVelocity(Vector2 pVelocity)
{
	velocity = pVelocity;
}

void RigidBody::AddVelocity(Vector2 pVelocity, VelocityType pVelocityType)
{
	switch (pVelocityType)
	{
	case RigidBody::continuous:
		velocity += ((pVelocity) * (float)unitSize) * deltaTime;
		break;
	case RigidBody::instant:
		velocity += pVelocity * (float)unitSize;
		break;
	}
}

void RigidBody::HandleCollision(Collision collision)
{
	if (collider->isTrigger)
	{
		return;
	}

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

	Vector2 newPos = object->position + velocity * collision.collisionTime;
	object->SetPosition(newPos);

	//std::cout << object->GetID() << ": " << newPos.printVector();

	float dotProduct = (velocity.x * collision.normal.y + velocity.y * collision.normal.x) * collision.remainingTime;
	velocity = Vector2(dotProduct * collision.normal.y, dotProduct * collision.normal.x);

	if (friction > 0 && velocity.GetLength() > 0)
	{
		float tFriction = (velocity.GetLength() * velocity.GetLength()) * friction;
		Vector2 frictionVector = velocity.normalized * tFriction * deltaTime;
		velocity -= frictionVector;
	}
}

void RigidBody::Move()
{
	object->SetPosition(object->position + velocity * deltaTime);
}

void RigidBody::ApplyDrag()
{
	float tDrag = velocity.GetLength() * drag;
	Vector2 dragVector = (velocity.normalized) * tDrag * deltaTime;

	velocity -= dragVector;

	if (velocity.GetLength() <= 0.001f)
		velocity = Vector2(0, 0);
}

void RigidBody::ApplyGravity()
{
	velocity += Vector2(0, gravity);
}