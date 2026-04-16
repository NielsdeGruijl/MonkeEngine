#include "TwoDimensionalSAP.h"
#include <iostream>
#include "../Objects/GameObject.h"

void TwoDimensionalSAP::RemoveExpiredReferences()
{
	// Todo: fit all of these into one for loop

	// Clean up xEdges
	std::erase_if(xEdges, [&](EdgePoint edge)
	{
		return GetCollider(edge.colliderId).expired();
	});

	// Clean up yEdges
	std::erase_if(yEdges, [&](EdgePoint edge)
	{
		return GetCollider(edge.colliderId).expired();
	});

	std::erase_if(tColliders, [](ColliderIdContainer collider)
	{
		return collider.collider.expired();
	});
}

void TwoDimensionalSAP::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{

	xEdges.emplace_back(colliderId, edgeId, &pCollider->left, true);
	yEdges.emplace_back(colliderId, edgeId, &pCollider->top, true);
	edgeId++;
	xEdges.emplace_back(colliderId, edgeId, &pCollider->right, false);
	yEdges.emplace_back(colliderId, edgeId, &pCollider->bottom, false);
	edgeId++;

	tColliders.emplace_back(pCollider, colliderId);

	colliderId++;
}

void TwoDimensionalSAP::Sweep(std::vector<int> pColliderIds)
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
				if (GetCollider(xCollision.first).expired() || GetCollider(xCollision.second).expired())
					break;

				std::cout << GetCollider(xCollision.first).lock()->object->GetID() << std::endl;
				std::cout << GetCollider(xCollision.second).lock()->object->GetID() << std::endl;

				collisionChecker.AddCollisionPair(GetCollider(xCollision.first), GetCollider(xCollision.second));

				break;
			}
		}
	}

	collisionChecker.CheckCollisionPairs();
}

void TwoDimensionalSAP::SweepX(std::vector<int> pColliderIds)
{
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

	// sort colliders left to right
	/*std::sort(pColliderIds.begin(), pColliderIds.end(), [this](int a, int b)
		{
			return *(xEdges[a].position) < *(xEdges[b].position);
		});*/

	// Go through all collider edges from left to right and every time a left edge is found, add it to touchingColliders
	// When a right edge is found, remove the left edge from touchingColliders
	// This way, all colliders with a left edge in touchingColliders, are overlapping on the X-axis
	std::vector<int> touchingColliders;

	for (EdgePoint edge : edges)
	{
		if (!edge.isEntry)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](int colliderId)
				{
					return colliderId == edge.colliderId;
				});

			if(it != touchingColliders.end())
				touchingColliders.erase(it);

			continue;
		}

		// Compare the current edge to all edges in touchingColliders, and mark them as overlapping on the x-axis
		for (int id : touchingColliders)
		{
			if (id == edge.colliderId)
				continue;

			if (auto colliderA = GetCollider(id).lock())
			{
				if (auto colliderB = GetCollider(edge.colliderId).lock())
				{
					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						xCollisions.push_back(std::make_pair(id, edge.colliderId));
					}
				}
			}
		}

		// Add the current (left) edge to touching colliders
		touchingColliders.push_back(edge.colliderId);
	}

	/*for (int i : pColliderIds)
	{
		const EdgePoint& edge = xEdges[i];

		// If the current edge is the right edge of a collider, look for it's sibling (left edge) and remove it from the touching colliders
		if (!edge.isEntry)
		{
			auto it = std::find_if(touchingColliders.begin(), touchingColliders.end(), [edge](int colliderId)
				{
					return colliderId == edge.colliderId;
				});

			if(it != touchingColliders.end())
				touchingColliders.erase(it);

			continue;
		}

		// Compare the current edge to all edges in touchingColliders, and mark them as overlapping on the x-axis
		for (int id : touchingColliders)
		{
			if (id == edge.colliderId)
				continue;

			if (auto colliderA = GetCollider(id).lock())
			{
				if (auto colliderB = GetCollider(edge.colliderId).lock())
				{
					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						xCollisions.push_back(std::make_pair(id, edge.colliderId));
					}
				}
			}
		}

		// Add the current (left) edge to touching colliders
		touchingColliders.push_back(edge.colliderId);
	}*/
}

// Sweep Y axis for possible overlapping colliders.
// Refer to SweepX for more explanation
void TwoDimensionalSAP::SweepY(std::vector<int> pColliderIds)
{
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
}

std::weak_ptr<AABBCollider> TwoDimensionalSAP::GetCollider(int pColliderId)
{
	auto it = std::find_if(tColliders.begin(), tColliders.end(), [pColliderId](ColliderIdContainer pColliderIdContainer)
	{
		return pColliderIdContainer.colliderId == pColliderId;
	});

	return it->collider;
}

const EdgePoint& TwoDimensionalSAP::GetXColliderEdge(int pColliderId, bool isEntry)
{
	auto it = std::find_if(xEdges.begin(), xEdges.end(), [pColliderId, isEntry](EdgePoint pEdge)
	{
		return pEdge.colliderId == pColliderId && pEdge.isEntry == isEntry;
	});

	return *it;
}

const EdgePoint & TwoDimensionalSAP::GetYColliderEdge(int pColliderId, bool isEntry)
{
	auto it = std::find_if(yEdges.begin(), yEdges.end(), [pColliderId, isEntry](EdgePoint pEdge)
{
	return pEdge.colliderId == pColliderId && pEdge.isEntry == isEntry;
});

	return *it;
}
