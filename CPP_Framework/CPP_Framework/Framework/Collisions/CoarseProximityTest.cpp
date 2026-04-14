//#pragma once
#include "CoarseProximityTest.h"
#include "../Objects/GameObject.h"

void CoarseProximityTest::MSAP()
{
	SortColliders();

	for (int i = 0; i < colliders.size(); i++)
	{
		bool addedColliderA = false;
		colliderIndexes.clear();
		if (auto colliderA = colliders[i].collider.lock())
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				if (auto colliderB = colliders[j].collider.lock())
				{
					bool tooFar = colliderB->object->position.x - colliderB->circleRadius > colliderA->object->position.x + colliderA->circleRadius;
					if (tooFar)
						break;

					Vector2 distance = colliderA->object->position - colliderB->object->position;

					if (distance.GetLength() <= colliderA->circleRadius + colliderB->circleRadius)
					{
						if (!addedColliderA)
						{
							int id = colliders[i].colliderId * 2;
							if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
							{
								colliderIndexes.push_back(id);
								colliderIndexes.push_back(id + 1);
							}

							addedColliderA = true;
						}

						int id = colliders[j].colliderId * 2;
						if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
						{
							colliderIndexes.push_back(id);
							colliderIndexes.push_back(id + 1);
						}
					}
				}
			}
			multiSweepAndPrune->Sweep(colliderIndexes);
		}
	}
}

void CoarseProximityTest::SAP()
{
	SortColliders();

	for (int i = 0; i < colliders.size(); i++)
	{
		bool addedColliderA = false;
		colliderIndexes.clear();
		if (auto colliderA = colliders[i].collider.lock())
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				if (auto colliderB = colliders[j].collider.lock())
				{
					bool tooFar = colliderB->object->position.x - colliderB->circleRadius > colliderA->object->position.x + colliderA->circleRadius;
					if (tooFar)
						break;

					Vector2 distance = colliderA->object->position - colliderB->object->position;

					if (distance.GetLength() <= colliderA->circleRadius + colliderB->circleRadius)
					{
						if (!addedColliderA)
						{
							int id = colliders[i].colliderId * 2;
							if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
							{
								colliderIndexes.push_back(id);
								colliderIndexes.push_back(id + 1);
							}

							addedColliderA = true;
						}

						int id = colliders[j].colliderId * 2;
						if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
						{
							colliderIndexes.push_back(id);
							colliderIndexes.push_back(id + 1);
						}
					}
				}
			}
			sweepAndPrune->Sweep(colliderIndexes);
		}
	}
}

void CoarseProximityTest::BruteForceExecution()
{
	SortColliders();

	for (int i = 0; i < colliders.size(); i++)
	{
		bool addedColliderA = false;
		colliderIndexes.clear();
		if (auto colliderA = colliders[i].collider.lock())
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				if (auto colliderB = colliders[j].collider.lock())
				{
					bool tooFar = colliderB->object->position.x - colliderB->circleRadius > colliderA->object->position.x + colliderA->circleRadius;
					if (tooFar)
						break;

					Vector2 distance = colliderA->object->position - colliderB->object->position;

					if (distance.GetLength() <= colliderA->circleRadius + colliderB->circleRadius)
					{
						if (!addedColliderA)
						{
							int id = colliders[i].colliderId;
							if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
								colliderIndexes.push_back(id);

							addedColliderA = true;
						}

						int id = colliders[j].colliderId;
						if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
							colliderIndexes.push_back(id);
					}
				}
			}
			bruteForce->CheckCollisions(colliderIndexes);
		}
	}
}

void CoarseProximityTest::RegisterCollider(std::weak_ptr<AABBCollider> pCollider)
{
	colliders.push_back(ColliderIdContainer(pCollider, colliderId));
	colliderId++;
}

void CoarseProximityTest::SortColliders()
{
	std::sort(colliders.begin(), colliders.end(), [](ColliderIdContainer a, ColliderIdContainer b)
		{
			return (a.collider.lock()->object->position.x < b.collider.lock()->object->position.x);
		});
}