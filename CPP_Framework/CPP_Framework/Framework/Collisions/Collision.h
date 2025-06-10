#pragma once

#include "../Objects/GameObject.h"
#include "../Components/RigidBody.h"

struct Collision
{
	Collision(GameObject* pObject, Vector2 pNormal, float pCollisionTime)
		: object(pObject), normal(pNormal)
	{
		//object->TryGetComponent<RigidBody>(rigidBody);

		remainingTime = 1 + collisionTime;

		//std::cout << normal.printVector();

		if (isnan(pCollisionTime))
		{
			collisionTime = 0;
			std::cout << object->GetID() << "\n";
			std::cout << normal.printVector();
			std::cout << "Nan\n";
		}
		else 
		{
			collisionTime = pCollisionTime;
		}
	}
	~Collision()
	{
	}


	GameObject* object;
	std::shared_ptr<RigidBody> rigidBody;

	Vector2 normal;

	float collisionTime = 0;
	float remainingTime = 0;
};