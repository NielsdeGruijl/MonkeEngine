#include "SweepAndPrune.h"

void SweepAndPrune::Sweep()
{
	SortEdgePoints();

	for (EdgePoint edge : edgePoints)
	{
		if (!edge.isLeft)
		{
			RemoveTouchingCollider(edge.collider);
			continue;
		}

		if (touchingColliders.size() > 0)
		{
			Prune(edge.collider);
		}

		touchingColliders.push_back(edge.collider);
	}

	collisionChecker.CheckCollisionPairs();
}

void SweepAndPrune::Prune(std::weak_ptr<AABBCollider> pCollider)
{
	for (std::weak_ptr<AABBCollider> collider : touchingColliders)
	{
		if (auto colliderA = collider.lock())
		{
			if (auto colliderB = pCollider.lock())
			{
				// If on of the objects is dynamic (AKA can collide), proceed to narrow phase
				if (colliderA->isDynamic || colliderB->isDynamic)
				{
					collisionChecker.AddCollisionPair(colliderA, colliderB);
					//collisionChecker.CheckCollision(colliderA, colliderB);
				}
			}
		}
	}
}

void SweepAndPrune::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	edgePoints.push_back(EdgePoint(pCollider, true));
	edgePoints.push_back(EdgePoint(pCollider, false));
}

void SweepAndPrune::SortEdgePoints()
{
	std::sort(edgePoints.begin(), edgePoints.end(), [](EdgePoint edgePointA, EdgePoint edgePointB)
		{
			return *edgePointA.position < *edgePointB.position;
		});
}

void SweepAndPrune::RemoveTouchingCollider(std::weak_ptr<AABBCollider> pColliderA)
{
	auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [pColliderA](std::weak_ptr<AABBCollider> pColliderB)
		{
			return pColliderB.lock() == pColliderA.lock();
		});

	touchingColliders.erase(it);
}