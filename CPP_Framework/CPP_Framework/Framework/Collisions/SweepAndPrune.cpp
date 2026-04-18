#include "SweepAndPrune.h"
#include "../Objects/GameObject.h"

void SweepAndPrune::Sweep(std::vector<int> pColliderIndexes)
{
	std::vector<int> edgeIds;

	for (int i : pColliderIndexes)
	{
		edgeIds.push_back(edgePairs[i].first);
		edgeIds.push_back(edgePairs[i].second);
	}

	std::sort(edgeIds.begin(), edgeIds.end(), [this](int a, int b)
		{
			return *edges[a].position < *edges[b].position;
		});

	touchingColliders.clear();

	for (int i : pColliderIndexes)
	{
		const EdgePoint& edge = edges[i];

		if (!edge.isEntry)
		{
			RemoveTouchingCollider(edge.colliderId);
			continue;
		}
		
		if (!touchingColliders.empty())
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

		if (auto colliderA = colliders[colliderId].lock())
		{
			if (auto colliderB = colliders[pColliderId].lock())
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
	int firstId = edgeId;
	edges.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->left, true));
	edgeId++;
	edges.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->right, false));
	//edgePoints.push_back(EdgePoint(colliderId, &pCollider->right, false));

	edgePairs.emplace(colliderId, std::pair<int, int>(firstId, edgeId));
	colliders[colliderId] = pCollider;

	edgeId++;

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