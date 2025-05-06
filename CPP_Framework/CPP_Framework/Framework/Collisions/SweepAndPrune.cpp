#include "SweepAndPrune.h"

void SweepAndPrune::Sweep()
{
	SortEdgePoints();

	touchingColliders.clear();

	for (const EdgePoint& edge : edgePoints)
	{
		if (!edge.isLeft)
		{
			RemoveTouchingCollider(edge.colliderId);
			continue;
		}
		
		if (touchingColliders.size() > 0)
		{
			Prune(edge.colliderId);
		}
		
		touchingColliders.push_back(edge.colliderId);
	}

	collisionChecker.CheckCollisionPairs();
}

void SweepAndPrune::Prune(int pColliderId)
{
	for (int colliderId : touchingColliders)
	{
		if (colliderId == pColliderId)
			continue;

		if (auto colliderA = colliders.at(colliderId).lock())
		{
			if (auto colliderB = colliders.at(pColliderId).lock())
			{
				// If on of the objects is dynamic (AKA can collide), proceed to narrow phase
				if (colliderA->isDynamic || colliderB->isDynamic)
				{
					collisionChecker.AddCollisionPair(std::move(CollisionPair(colliderA, colliderB)));
				}
			}
		}
	}
}

void SweepAndPrune::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	edgePoints.push_back(EdgePoint(colliderId, &pCollider->left, true));
	edgePoints.push_back(EdgePoint(colliderId, &pCollider->right, false));
	colliders.push_back(pCollider);

	colliderId++;
}

void SweepAndPrune::SortEdgePoints()
{
	std::sort(edgePoints.begin(), edgePoints.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
		{
			return *edgePointA.position < *edgePointB.position;
		});
}

void SweepAndPrune::RemoveTouchingCollider(int pColliderAId)
{
	auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [pColliderAId](int pColliderBId)
		{
			return pColliderAId == pColliderBId;
		});

	touchingColliders.erase(it);
}