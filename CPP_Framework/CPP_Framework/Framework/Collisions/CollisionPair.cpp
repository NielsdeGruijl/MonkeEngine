#include "CollisionPair.h"

CollisionPair::CollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
{
	colliderA = pColliderA;
	colliderB = pColliderB;
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
	//std::cout << "Collision pair destroyed\n";
}

void CollisionPair::OnEnter()
{
	if (auto tColliderA = colliderA.lock())
	{
		if (auto tColliderB = colliderB.lock())
		{
			//std::cout << "New collision pair created: " << tColliderA->object->GetID() << ", " << tColliderB->object->GetID() << "\n";
			tColliderA->SetCollisionState(tColliderB, AABBCollider::enter);
		}
	}
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
	if (colliderA.lock().get() == pCollisionPair->colliderA.lock().get() && colliderB.lock().get() == pCollisionPair->colliderB.lock().get())
	{
		if (colliderA.lock().get() == pCollisionPair->colliderB.lock().get() && colliderB.lock().get() == pCollisionPair->colliderA.lock().get())
		{
			return true;
		}
	}
	return false;
}

bool CollisionPair::operator==(CollisionPair pCollisionPair)
{
	auto a = colliderA.lock();
	auto b = colliderB.lock();
	auto a2 = pCollisionPair.colliderA.lock();
	auto b2 = pCollisionPair.colliderB.lock();

	if (a == nullptr || b == nullptr || a2 == nullptr || b2 == nullptr)
		return false;

	return (a == a2 || a == b2) && (b == a2 || b == b2);
}