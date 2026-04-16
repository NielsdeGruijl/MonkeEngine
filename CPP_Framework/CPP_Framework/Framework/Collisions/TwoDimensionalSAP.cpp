#include "TwoDimensionalSAP.h"
#include <iostream>
#include "../Objects/GameObject.h"

void TwoDimensionalSAP::RegisterCollider(std::shared_ptr<AABBCollider> pCollider)
{
	xEdges.push_back(EdgePoint(colliderId, &pCollider->left, true));
	xEdges.push_back(EdgePoint(colliderId, &pCollider->right, false));
	yEdges.push_back(EdgePoint(colliderId, &pCollider->top, true));
	yEdges.push_back(EdgePoint(colliderId, &pCollider->bottom, false));
	colliders.push_back(pCollider);
	tColliders.push_back(ColliderIdContainer(pCollider, colliderId));

	colliderId++;
}

void TwoDimensionalSAP::Sweep(std::vector<int> pColliderIds)
{
	xCollisions.clear();
	yCollisions.clear();

	for (auto collider : colliders)
	{
		if (collider.expired())
		{
			std::cout << "collider expired\n";
			continue;
		}

		std::cout << collider.lock()->object->GetID() << std::endl;
	}

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
				if (colliders.at(xCollision.first).expired() || colliders.at(xCollision.second).expired())
					break;

				std::cout << colliders.at(xCollision.first).lock()->object->GetID() << std::endl;
				std::cout << colliders.at(xCollision.second).lock()->object->GetID() << std::endl;

				collisionChecker.AddCollisionPair(colliders.at(xCollision.first), colliders.at(xCollision.second));

				break;
			}
		}
	}

	collisionChecker.CheckCollisionPairs();
}

void TwoDimensionalSAP::SweepX(std::vector<int> pColliderIds)
{
	// sort colliders left to right
	std::sort(pColliderIds.begin(), pColliderIds.end(), [this](int a, int b)
		{
			return *(xEdges[a].position) < *(xEdges[b].position);
		});

	// Go through all collider edges from left to right and every time a left edge is found, add it to touchingColliders
	// When a right edge is found, remove the left edge from touchingColliders
	// This way, all colliders with a left edge in touchingColliders, are overlapping on the X-axis
	std::vector<int> touchingColliders;
	for (int i : pColliderIds)
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

			if (auto colliderA = colliders.at(id).lock())
			{
				if (auto colliderB = colliders.at(edge.colliderId).lock())
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
}

// Sweep Y axis for possible overlapping colliders.
// Refer to SweepX for more explanation
void TwoDimensionalSAP::SweepY(std::vector<int> pColliderIds)
{
	std::sort(pColliderIds.begin(), pColliderIds.end(), [this](int a, int b)
		{
			return *(yEdges[a].position) < *(yEdges[b].position);
		});

	std::vector<int> touchingColliders;
	for (int i : pColliderIds)
	{
		const EdgePoint& edge = yEdges[i];

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
			if (auto colliderA = colliders.at(id).lock())
			{
				if (auto colliderB = colliders.at(edge.colliderId).lock())
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