#include "TwoDimensionalSAP.h"
#include <iostream>

void TwoDimensionalSAP::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	xEdges.push_back(EdgePoint(pCollider, &pCollider->left, true));
	xEdges.push_back(EdgePoint(pCollider, &pCollider->right, false));
	yEdges.push_back(EdgePoint(pCollider, &pCollider->top, true));
	yEdges.push_back(EdgePoint(pCollider, &pCollider->bottom, false));
}

void TwoDimensionalSAP::Sweep()
{
	xPossibleCollisions.clear();
	yPossibleCollisions.clear();

	SweepX();
	SweepY();

	std::sort(yPossibleCollisions.begin(), yPossibleCollisions.end(), [](const CollisionPair& pairA, const CollisionPair& pairB)
	{
			return pairA.colliderA.lock()->left < pairB.colliderA.lock()->left;
	});


	for (CollisionPair xCollision : xPossibleCollisions)
	{
		for (CollisionPair yCollision : yPossibleCollisions)
		{
			if (yCollision.colliderA.lock()->left > xCollision.colliderB.lock()->right)
				continue;
	
			if (xCollision == yCollision)
				collisionChecker.AddCollisionPair(std::move(xCollision));
		}
	}

	collisionChecker.CheckCollisionPairs();
}

void TwoDimensionalSAP::SweepX()
{
	std::sort(xEdges.begin(), xEdges.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
		{
			return *(edgePointA.position) < *(edgePointB.position);
		});

	std::vector<std::weak_ptr<AABBCollider>> touchingColliders;
	for (EdgePoint edge : xEdges)
	{
		if (!edge.isLeft)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](std::weak_ptr<AABBCollider> pColliderB)
				{
					return pColliderB.lock() == edge.collider.lock();
				});
		
			touchingColliders.erase(it);
			continue;
		}

		for (std::weak_ptr<AABBCollider> collider : touchingColliders)
		{
			if (auto colliderA = collider.lock())
			{
				if (auto colliderB = edge.collider.lock())
				{
					if (colliderA == colliderB)
						continue;

					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						xPossibleCollisions.push_back(CollisionPair(colliderA, colliderB));
					}
				}
			}
		}

		touchingColliders.push_back(edge.collider);
	}
}

void TwoDimensionalSAP::SweepY()
{
	std::sort(yEdges.begin(), yEdges.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
		{
			return *(edgePointA.position) < *(edgePointB.position);
		});

	std::vector<std::weak_ptr<AABBCollider>> touchingColliders;
	for (EdgePoint edge : yEdges)
	{
		if (!edge.isLeft)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](std::weak_ptr<AABBCollider> pColliderB)
				{
					return pColliderB.lock() == edge.collider.lock();
				});

			touchingColliders.erase(it);
			continue;
		}

		for (std::weak_ptr<AABBCollider> collider : touchingColliders)
		{
			if (auto colliderA = collider.lock())
			{
				if (auto colliderB = edge.collider.lock())
				{
					if (colliderA == colliderB)
						continue;

					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						yPossibleCollisions.push_back(CollisionPair(colliderA, colliderB));
					}
				}
			}
		}

		touchingColliders.push_back(edge.collider);
	}
}
