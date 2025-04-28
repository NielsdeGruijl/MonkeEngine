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

		touchingColliders.push_back(edge.collider);

		if (touchingColliders.size() > 1)
		{
			Prune(edge.collider);
		}
	}
}

void SweepAndPrune::Prune(std::weak_ptr<AABBCollider> pCollider)
{
	for (std::weak_ptr<AABBCollider> collider : touchingColliders)
	{
		if (auto colliderA = collider.lock())
		{
			if (auto colliderB = pCollider.lock())
			{
				if (colliderA == colliderB)
					continue;

				std::shared_ptr<RigidBody> rbA, rbB;

				// If on of the objects is not static, proceed to narrow phase
				if (colliderA->object->TryGetComponent<RigidBody>(rbA) || colliderB->object->TryGetComponent<RigidBody>(rbB))
				{
					collisionChecker.CheckCollision(colliderA, colliderB);
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