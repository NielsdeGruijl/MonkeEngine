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

void TwoDimensionalSAP::RegisterColliders()
{
	std::sort(tColliders.begin(), tColliders.end(), [](ColliderIdContainer a, ColliderIdContainer b)
		{
			return (a.collider.lock()->object->position.x < b.collider.lock()->object->position.x);
		});

	for (int i = 0; i < tColliders.size(); i++)
	{
		xEdgeIndexes.clear();
		yEdgeIndexes.clear();
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
								yEdgeIndexes.push_back(id);
								yEdgeIndexes.push_back(id + 1);
							}

							addedColliderA = true;
						}

						int id = tColliders[j].colliderId * 2;
						if (std::find(xEdgeIndexes.begin(), xEdgeIndexes.end(), id) == xEdgeIndexes.end())
						{
							xEdgeIndexes.push_back(id);
							xEdgeIndexes.push_back(id + 1);
							yEdgeIndexes.push_back(id);
							yEdgeIndexes.push_back(id + 1);
						}
					}
				}
			}

			Sweep();
		}
	}

}

void TwoDimensionalSAP::Sweep()
{
	xCollisions.clear();
	yCollisions.clear();

	//std::cout << xEdgeIndexes.size() << ", " << yEdgeIndexes.size() << "\n";

	SweepX();
	SweepY();

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

void TwoDimensionalSAP::SweepX()
{
	//std::sort(xEdges.begin(), xEdges.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
	//	{
	//		return *(edgePointA.position) < *(edgePointB.position);
	//	});

	std::sort(xEdgeIndexes.begin(), xEdgeIndexes.end(), [this](int a, int b)
		{
			return *(xEdges[a].position) < *(xEdges[b].position);
		});

	std::vector<int> touchingColliders;
	for (int i : xEdgeIndexes)
	{
		const EdgePoint& edge = xEdges[i];

		if (!edge.isLeft)
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

void TwoDimensionalSAP::SweepY()
{
	//std::sort(yEdges.begin(), yEdges.end(), [](const EdgePoint& edgePointA, const EdgePoint& edgePointB)
	//	{
	//		return *(edgePointA.position) < *(edgePointB.position);
	//	});

	std::sort(yEdgeIndexes.begin(), yEdgeIndexes.end(), [this](int a, int b)
		{
			return *(yEdges[a].position) < *(yEdges[b].position);
		});

	std::vector<int> touchingColliders;
	for (int i : yEdgeIndexes)
	{

		const EdgePoint& edge = yEdges[i];

		if (!edge.isLeft)
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