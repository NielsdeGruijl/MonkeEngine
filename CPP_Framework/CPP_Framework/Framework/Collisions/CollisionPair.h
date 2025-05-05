#include "AABBCollider.h"

class CollisionPair
{
public:
	CollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB);
	~CollisionPair();

	void OnEnter();

	bool DoesCollisionPairExist(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB);

	bool operator==(CollisionPair* pCollisionPair);
	bool operator==(CollisionPair pCollisionPair);

	std::weak_ptr<AABBCollider> colliderA, colliderB;
};