#include "SweepAndPrune.h"
#include "../Objects/GameObject.h"

void SweepAndPrune::Sweep()
{
	SortEdgePoints();

	touchingColliders.clear();

	for (int i : xEdgeIndexes)
	{
		const EdgePoint& edge = edgePoints[i];

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
	tColliders.push_back(ColliderIdContainer(pCollider, colliderId));
	colliders.push_back(pCollider);

	colliderId++;
}

void SweepAndPrune::SweepPhase()
{
	xEdgeIndexes.clear();

	std::sort(tColliders.begin(), tColliders.end(), [](ColliderIdContainer a, ColliderIdContainer b)
		{
			return (a.collider.lock()->object->position.x < b.collider.lock()->object->position.x);
		});

	for (int i = 0; i < tColliders.size(); i++)
	{
		xEdgeIndexes.clear();
		if (shared_ptr<AABBCollider> colliderA = tColliders[i].collider.lock())
		{
			bool addedColliderA = false;
			for (int j = i + 1; j < tColliders.size(); j++)
			{
				if (shared_ptr<AABBCollider> colliderB = tColliders[j].collider.lock())
				{
					bool tooFar = colliderB->object->position.x - colliderB->circleRadius > colliderA->object->position.x + colliderA->circleRadius;
					if (tooFar)
						break;

					Vector2 distance = colliderA->object->position - colliderB->object->position;

					if (distance.GetLength() <= colliderA->circleRadius + colliderB->circleRadius)
					{
						if (!addedColliderA)
						{
							int id = tColliders[i].colliderId * 2;
							if (std::find(xEdgeIndexes.begin(), xEdgeIndexes.end(), id) == xEdgeIndexes.end())
							{
								xEdgeIndexes.push_back(id);
								xEdgeIndexes.push_back(id + 1);
							}

							addedColliderA = true;
						}

						int id = tColliders[j].colliderId * 2;
						if (std::find(xEdgeIndexes.begin(), xEdgeIndexes.end(), id) == xEdgeIndexes.end())
						{
							xEdgeIndexes.push_back(id);
							xEdgeIndexes.push_back(id + 1);
						}
					}
				}
			}

			Sweep();
		}
	}
}

void SweepAndPrune::SortEdgePoints()
{
	//std::sort(edgePoints.begin(), edgePoints.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
	//	{
	//		return *edgePointA.position < *edgePointB.position;
	//	});

	std::sort(xEdgeIndexes.begin(), xEdgeIndexes.end(), [this](int a, int b)
		{
			return *(edgePoints[a].position) < *(edgePoints[b].position);
		});
}

void SweepAndPrune::RemoveTouchingCollider(int pColliderAId)
{
	auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [pColliderAId](int pColliderBId)
		{
			return pColliderAId == pColliderBId;
		});

	if(it != touchingColliders.end())
		touchingColliders.erase(it);
}