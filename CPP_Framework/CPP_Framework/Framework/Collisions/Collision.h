#pragma once

#include "../Objects/Object.h"
#include "../Components/RigidBody.h"

struct Collision
{
	Collision(Object* pObject, Vector2 pNormal, float pCollisionTime)
	{
		object = pObject;
		object->TryGetComponent(rigidBody);

		normal = pNormal;

		collisionTime = pCollisionTime;
		remainingTime = 1 + pCollisionTime;
	}
	~Collision()
	{
	}

	Object* object;
	std::shared_ptr<RigidBody> rigidBody;

	Vector2 normal;

	float collisionTime;
	float remainingTime;
};