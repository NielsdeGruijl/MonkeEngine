#include "BruteForce.h"

void BruteForce::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	colliders.push_back(pCollider);
}

void BruteForce::CheckCollisions()
{
	SortColliders();

	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i + 1; j < colliders.size(); j++)
		{
			if (auto colliderA = colliders[i].lock())
			{
				if (auto colliderB = colliders[j].lock())
				{
					if (colliderB->left > colliderA->right + 1)
						break;

					//collisionChecker.AddCollisionPair(colliderA, colliderB);
					//collisionChecker.CheckCollision(colliderA, colliderB);

					std::shared_ptr<RigidBody> rbA, rbB;
					if (colliderA->object->TryGetComponent<RigidBody>(rbA) || colliderB->object->TryGetComponent<RigidBody>(rbB))
					{
						collisionChecker.AddCollisionPair(colliderA, colliderB);
						//collisionChecker.CheckCollision(colliderA, colliderB);
					}
				}
			}
		}
	}

	collisionChecker.CheckCollisionPairs();
}

void BruteForce::SortColliders()
{
	RemoveExpiredReferences();

	std::sort(colliders.begin(), colliders.end(), [](std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
		{
			std::shared_ptr<AABBCollider> colliderA = pColliderA.lock();
			std::shared_ptr<AABBCollider> colliderB = pColliderB.lock();

			return colliderA->left < colliderB->left;
		});
}

void BruteForce::RemoveExpiredReferences()
{
	float amountOfExpiredColliders = 0;
	
	for (std::weak_ptr<AABBCollider> rigidBody : colliders)
	{
		if (rigidBody.expired())
			amountOfExpiredColliders++;
	}
	
	while (amountOfExpiredColliders > 0)
	{
		colliders.erase(
			std::remove_if(colliders.begin(), colliders.end(),
				[](std::weak_ptr<AABBCollider> collider)
				{
					return collider.expired();
				}),
			colliders.end());
	
		amountOfExpiredColliders--;
	}
}
