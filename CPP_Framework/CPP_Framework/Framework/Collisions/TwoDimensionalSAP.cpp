#include "TwoDimensionalSAP.h"
#include <iostream>
#include "../Objects/GameObject.h"

void TwoDimensionalSAP::RemoveExpiredReferences()
{
	// Todo: fit all of these into one for loop

	// Clean up xEdges
	/*std::erase_if(xEdges, [&](EdgePoint edge)
	{
		return GetCollider(edge.colliderId).expired();
	});

	// Clean up yEdges
	std::erase_if(yEdges, [&](EdgePoint edge)
	{
		return GetCollider(edge.colliderId).expired();
	});*/

	std::erase_if(tColliders, [](ColliderIdContainer collider)
	{
		return collider.collider.expired();
	});
}

void TwoDimensionalSAP::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	// Store first edge id to add to index map
	int firstId = edgeId;

	xEdgeIdMap.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->left, true));
	yEdgeIdMap.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->top, true));
	edgeId++;

	xEdgeIdMap.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->right, false));
	yEdgeIdMap.emplace(edgeId, EdgePoint(colliderId, edgeId, &pCollider->bottom, false));

	edgeMap.emplace(colliderId, std::pair<int, int>(firstId, edgeId));

	edgeId++;

	colliders[colliderId] = pCollider;
	tColliders.emplace_back(pCollider, colliderId);

	colliderId++;
}

void TwoDimensionalSAP::Sweep(std::vector<int> pColliderIds)
{
	for (int i = 0; i < 5; i++)
	{
		xCollisions.clear();
		yCollisions.clear();

		RemoveExpiredReferences();

		// First "sweeps" to check for collisions on the X-axis
		SweepX(pColliderIds);
		// Then "sweeps" to check for collisions on the Y-axis
		SweepY(pColliderIds);

		for (std::pair<int, int> xCollision : xCollisions)
		{
			for (std::pair<int, int> yCollision : yCollisions)
			{
				// If a collision "pair" from the X-axis collisions also exists on the Y-axis collisions, mark it as a potential collision
				if ((xCollision.first == yCollision.first && xCollision.second == yCollision.second) ||
					(xCollision.second == yCollision.first && xCollision.first == yCollision.second))
				{
					if (colliders[xCollision.first].expired() || colliders[xCollision.second].expired())
						break;

					collisionChecker.AddCollisionPair(colliders[xCollision.first], colliders[xCollision.second]);

					break;
				}
			}
		}

		collisionChecker.CheckCollisionPairs();
	}
}

void TwoDimensionalSAP::SweepX(std::vector<int> pColliderIds)
{
	//Timer timer = Timer("SweepX");
	std::vector<int> edgeIds;

	for (auto id : pColliderIds)
	{
		edgeIds.push_back(edgeMap[id].first);
		edgeIds.push_back(edgeMap[id].second);
	}

	std::sort(edgeIds.begin(), edgeIds.end(), [&](int a, int b)
	{
		return *xEdgeIdMap[a].position < *xEdgeIdMap[b].position;
	});

	std::vector<int> touchingColliders;

	// Go through all collider edges from left to right and every time a left edge is found, add it to touchingColliders
	// When a right edge is found, remove the left edge from touchingColliders
	// This way, all colliders with a left edge in touchingColliders, are overlapping on the X-axis
	for (int i : edgeIds)
	{
		EdgePoint* edge = &xEdgeIdMap.at(i);

		if (!edge->isEntry)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](int colliderId)
				{
					return colliderId == edge->colliderId;
				});

			if(it != touchingColliders.end())
				touchingColliders.erase(it);

			continue;
		}

		// Compare the current edge to all edges in touchingColliders, and mark them as overlapping on the x-axis
		for (int id : touchingColliders)
		{
			if (id == edge->colliderId)
				continue;

			if (auto colliderA = colliders[id].lock())
			{
				if (auto colliderB = colliders[edge->colliderId].lock())
				{
					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						xCollisions.push_back(std::make_pair(id, edge->colliderId));
					}
				}
			}
		}

		// Add the current (left) edge to touching colliders
		touchingColliders.push_back(edge->colliderId);
	}
}

/*void TwoDimensionalSAP::SweepX(std::vector<int> pColliderIds)
{
	Timer timer = Timer("SweepX");
	std::vector<EdgePoint> edges;

	for (auto id : pColliderIds)
	{
		for (auto edge : xEdges)
		{
			if (edge.colliderId == id)
			{
				edges.push_back(edge);
			}
		}
	}

	std::sort(edges.begin(), edges.end(), [](EdgePoint a, EdgePoint b)
	{
		return *a.position < *b.position;
	});

	std::vector<int> touchingColliders;
	for (EdgePoint edge : edges)
	{
		if (!edge.isEntry)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](int colliderId)
				{
					return colliderId == edge.colliderId;
				});

			if (it != touchingColliders.end())
				touchingColliders.erase(it);
			continue;
		}

		for (int id : touchingColliders)
		{
			if (auto colliderA = GetCollider(id).lock())
			{
				if (auto colliderB = GetCollider(edge.colliderId).lock())
				{
					if (colliderA == colliderB)
						continue;

					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						yCollisions.push_back(std::make_pair(id, edge.colliderId));
					}
				}
			}
		}

		touchingColliders.push_back(edge.colliderId);
	}
}*/

// Sweep Y axis for possible overlapping colliders.
// Refer to SweepX for more explanation
void TwoDimensionalSAP::SweepY(std::vector<int> pColliderIds)
{
	//Timer timer = Timer("SweepY");

	std::vector<int> edgeIds;

	for (auto id : pColliderIds)
	{
		edgeIds.push_back(edgeMap[id].first);
		edgeIds.push_back(edgeMap[id].second);
	}

	std::sort(edgeIds.begin(), edgeIds.end(), [&](int a, int b)
	{
		return *yEdgeIdMap[a].position < *yEdgeIdMap[b].position;
	});

	std::vector<int> touchingColliders;
	for (int i : edgeIds)
	{
		EdgePoint* edge = &yEdgeIdMap.at(i);

		if (!edge->isEntry)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](int colliderId)
				{
					return colliderId == edge->colliderId;
				});

			if (it != touchingColliders.end())
				touchingColliders.erase(it);
			continue;
		}

		for (int id : touchingColliders)
		{
			if (auto colliderA = colliders[id].lock())
			{
				if (auto colliderB = colliders[edge->colliderId].lock())
				{
					if (colliderA == colliderB)
						continue;

					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						yCollisions.push_back(std::make_pair(id, edge->colliderId));
					}
				}
			}
		}

		touchingColliders.push_back(edge->colliderId);
	}
}