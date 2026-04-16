#include "SweepAndPrune.h"
#include "../Objects/GameObject.h"

void SweepAndPrune::Sweep(std::vector<int> pColliderIndexes)
{
	std::sort(pColliderIndexes.begin(), pColliderIndexes.end(), [this](int a, int b)
		{
			return *(edgePoints[a].position) < *(edgePoints[b].position);
		});

	touchingColliders.clear();

	for (int i : pColliderIndexes)
	{
		const EdgePoint& edge = edgePoints[i];

		if (!edge.isEntry)
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
					collisionChecker.AddCollisionPair(colliderA, colliderB);
				}
			}
		}
	}
}

void SweepAndPrune::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	// ================= Add edge ids ================
	//edgePoints.push_back(EdgePoint(colliderId, &pCollider->left, true));
	//edgePoints.push_back(EdgePoint(colliderId, &pCollider->right, false));
	//tColliders.push_back(ColliderIdContainer(pCollider, colliderId));
	colliders.push_back(pCollider);

	colliderId++;
}

void SweepAndPrune::SortEdgePoints()
{
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