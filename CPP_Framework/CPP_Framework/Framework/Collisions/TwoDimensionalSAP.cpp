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

	SweepX(pColliderIds);
	SweepY(pColliderIds);

	for (std::pair<int, int> xCollision : xCollisions)
	{
		for (std::pair<int, int> yCollision : yCollisions)
		{
			if ((xCollision.first == yCollision.first && xCollision.second == yCollision.second) ||
				(xCollision.second == yCollision.first && xCollision.first == yCollision.second))
			{
				collisionChecker.AddCollisionPair(std::move(CollisionPair(colliders.at(xCollision.first), colliders.at(xCollision.second))));
			}
		}
	}

	collisionChecker.CheckCollisionPairs();
}

void TwoDimensionalSAP::SweepX(std::vector<int> pColliderIds)
{
	std::sort(pColliderIds.begin(), pColliderIds.end(), [this](int a, int b)
		{
			return *(xEdges[a].position) < *(xEdges[b].position);
		});

	std::vector<int> touchingColliders;
	for (int i : pColliderIds)
	{
		const EdgePoint& edge = xEdges[i];

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

		for (int colliderId : touchingColliders)
		{
			if (colliderId == edge.colliderId)
				continue;

			if (auto colliderA = colliders.at(colliderId).lock())
			{
				if (auto colliderB = colliders.at(edge.colliderId).lock())
				{
					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						xCollisions.push_back(std::make_pair(colliderId, edge.colliderId));
					}
				}
			}
		}

		touchingColliders.push_back(edge.colliderId);
	}
}

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

		for (int colliderId : touchingColliders)
		{
			if (auto colliderA = colliders.at(colliderId).lock())
			{
				if (auto colliderB = colliders.at(edge.colliderId).lock())
				{
					if (colliderA == colliderB)
						continue;

					if (colliderA->isDynamic || colliderB->isDynamic)
					{
						yCollisions.push_back(std::make_pair(colliderId, edge.colliderId));
					}
				}
			}
		}

		touchingColliders.push_back(edge.colliderId);
	}
}