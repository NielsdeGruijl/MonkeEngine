#include "BruteForce.h"
#include "../Objects/GameObject.h"

void BruteForce::RegisterCollider(std::weak_ptr<AABBCollider> pCollider)
{
	colliders.push_back(pCollider);
}

void BruteForce::CheckCollisions(std::vector<int> pColliderIndexes)
{
	for (int i = 0; i < pColliderIndexes.size(); i++)
	{
		for (int j = i + 1; j < pColliderIndexes.size(); j++)
		{
			if (auto colliderA = colliders[pColliderIndexes[i]].lock())
			{
				if (auto colliderB = colliders[pColliderIndexes[j]].lock())
				{
					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						if(colliderA->left < colliderB->left)
							collisionChecker.AddCollisionPair(colliderA, colliderB);
						else
							collisionChecker.AddCollisionPair(colliderB, colliderA);
					}
				}
			}
		}
	}

	collisionChecker.CheckCollisionPairs();
}