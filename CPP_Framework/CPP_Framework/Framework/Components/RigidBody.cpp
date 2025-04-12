#include <iostream>

#include "RigidBody.h"

#include "../Collisions/Collision.h"

extern const int unitSize;
extern float deltaTime;

RigidBody::RigidBody(Object* pObject)
	: Component(pObject)
{
	mass = 1;
	drag = 1;
	gravity = 9.81f;
	friction = 0;
	bounciness = 0;

	isGrounded = false;

	Vector2 tempObjectSize = object->GetSize();

	if (collider == nullptr)
		collider = object->AddComponent<AABBCollider>(object, &object->position);
}

RigidBody::~RigidBody()
{
	Component::~Component();
}

void RigidBody::OnLoad()
{
	Component::OnLoad();
}
	
void RigidBody::Update()
{
	Component::Update();

	if (gravity > 0)
		ApplyGravity();

	if (velocity.GetLength() > 0)
	{
		CalculateDrag();
		Move();
	}
}

void RigidBody::AddForce(Vector2 pForce, VelocityType pVelocityType)
{
	Vector2 tForce = pForce * (1 / mass);

	switch (pVelocityType)
	{
	case continuous:
		velocity += tForce * deltaTime;
		break;
	case instant:
		velocity += tForce;
		break;
	case velocityChange:
		velocity = tForce;
		break;
	}
}

void RigidBody::HandleCollision(Collision collision)
{
	if (collider->isTrigger)
		return;

	if (velocity.GetLength() > 0)
	{
		Vector2 positionAdjustment = velocity.normalized * collision.collisionTime;
		Vector2 newPos = object->position + positionAdjustment;
		object->SetPosition(newPos);
	}

	if (collision.rigidBody == nullptr)
	{
		float dotProduct = (velocity.x * collision.normal.y + velocity.y * collision.normal.x) * collision.remainingTime;
		velocity = Vector2(dotProduct * collision.normal.y, dotProduct * collision.normal.x);
	}

	if (friction > 0 && velocity.GetLength() > 0)
	{
		float tFriction = (velocity.GetLength() * velocity.GetLength()) * friction;
		Vector2 frictionVector = velocity.normalized * tFriction * deltaTime;
		AddForce(frictionVector * -1);
	}
}

void RigidBody::HandleBounce(std::shared_ptr<RigidBody> pRigidBody)
{
	float bounce = this->bounciness;
	if (bounce < pRigidBody->bounciness)
		bounce = pRigidBody->bounciness;

	float mass1 = mass;
	float mass2 = pRigidBody->mass;

	Vector2 v2 = pRigidBody->velocity;
	Vector2 v1 = velocity;

	//Vector2 normal = collider->position - pRigidBody->collider->position;
	//normal.Normalize();
	//Vector2 tangent = Vector2(-normal.y, normal.x);
	//
	//float v1n = v1.Dot(normal);
	//float v1t = v1.Dot(tangent);
	//float v2n = v2.Dot(normal);
	//float v2t = v2.Dot(tangent);
	//
	//float v1np = ((v1n * (mass1 - mass2)) + (2 * mass2 * v2n)) / (mass1 + mass2);
	//float v2np = ((v2n * (mass2 - mass1)) + (2 * mass1 * v1n)) / (mass1 + mass2);
	//
	//Vector2 v1p = (normal * v1np) + (tangent * v1t);
	//Vector2 v2p = (normal * v2np) + (tangent * v2t);
	//
	//AddForce(v1p * bounce * mass1, velocityChange);
	//pRigidBody->AddForce(v2p * bounce * mass2, velocityChange);

	return;
}

void RigidBody::Move()
{
	velocity -= dragForce;
	object->SetPosition(object->position + velocity * deltaTime * (float)unitSize);
}

void RigidBody::CalculateDrag()
{
	float tDrag = velocity.GetLength() * drag;
	dragForce = velocity.normalized * tDrag * deltaTime;

	if (velocity.GetLength() <= 0.001f)
		velocity = Vector2(0, 0);
}

void RigidBody::ApplyGravity()
{
	if (isGrounded)
		gravityForce = Vector2(0, 0);
	else
		gravityForce = Vector2(0, gravity);

	AddForce(gravityForce);
}