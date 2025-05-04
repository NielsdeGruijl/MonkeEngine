#include "CollisionPair.h"

CollisionPair::CollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
{
	colliderA = pColliderA;
	colliderB = pColliderB;

	if (auto tColliderA = colliderA.lock())
	{
		if (auto tColliderB = colliderB.lock())
		{
			std::cout << "New collision pair created: " << tColliderA->object->GetID() << ", " << tColliderB->object->GetID() << "\n";
			tColliderA->SetCollisionState(tColliderB, AABBCollider::enter);
		}
	}
}

CollisionPair::~CollisionPair()
{
	if (auto tColliderA = colliderA.lock())
	{
		if (auto tColliderB = colliderB.lock())
		{
			tColliderA->SetCollisionState(tColliderB, AABBCollider::exit);
		}
	}
	std::cout << "Collision pair destroyed\n";
}

bool CollisionPair::DoesCollisionPairExist(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
{
	if ((pColliderA.lock() == colliderA.lock() && pColliderB.lock() == colliderB.lock())
		|| (pColliderA.lock() == colliderB.lock() && pColliderB.lock() == colliderA.lock()))
	{
		return true;
	}
	return false;
}

bool CollisionPair::operator==(CollisionPair*pCollisionPair)
{
	if (colliderA.lock() == pCollisionPair->colliderA.lock() && colliderB.lock() == pCollisionPair->colliderB.lock())
	{
		if (colliderA.lock() == pCollisionPair->colliderB.lock() && colliderB.lock() == pCollisionPair->colliderA.lock())
		{
			return true;
		}
	}
	return false;
}
