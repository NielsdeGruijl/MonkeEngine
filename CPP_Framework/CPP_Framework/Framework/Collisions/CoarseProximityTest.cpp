//#pragma once
#include "CoarseProximityTest.h"
#include "../Objects/GameObject.h"

void CoarseProximityTest::MSAP()
{
	SortColliders();

	colliderIndexes.clear();

	for (int i = 0; i < colliders.size(); i++)
	{
		bool addedColliderA = false;

		if (auto colliderA = colliders[i].collider.lock())
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				if (auto colliderB = colliders[j].collider.lock())
				{
					// if object B's left boundary is further to the right than object A's right boundary
					bool tooFar = colliderB->object->position.x - colliderB->circleRadius > colliderA->object->position.x + colliderA->circleRadius;
					if (tooFar)
						break;

					if (!addedColliderA)
					{
						int id = colliders[i].colliderId;
						if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
						{
							colliderIndexes.push_back(id);
							//colliderIndexes.push_back(id + 1);
						}

						addedColliderA = true;
					}

					int id = colliders[j].colliderId;
					if (std::find(colliderIndexes.begin(), colliderIndexes.end(), id) == colliderIndexes.end())
					{
						colliderIndexes.push_back(id);
						//colliderIndexes.push_back(id + 1);
					}
				}
			}
		}
	}

	if (colliderIndexes.empty())
		return;

	multiSweepAndPrune->Sweep(colliderIndexes);

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
		}

		sweepAndPrune->Sweep(colliderIndexes);

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
	std::erase_if(colliders, [](ColliderIdContainer pCollider)
	{
		return pCollider.collider.expired();
	});

	std::sort(colliders.begin(), colliders.end(), [](ColliderIdContainer a, ColliderIdContainer b)
		{
			return (a.collider.lock()->object->position.x < b.collider.lock()->object->position.x);
		});
}

std::weak_ptr<AABBCollider> CoarseProximityTest::GetCollider(int id)
{
	auto it = std::find_if(colliders.begin(), colliders.end(), [id](ColliderIdContainer pCollider)
	{
		return pCollider.colliderId == id;
	});

	return it->collider;
}
