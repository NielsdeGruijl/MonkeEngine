#include "AABBCollider.h"
#include "CollisionChecker.h"

class BruteForce
{
public:
	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void CheckCollisions();

private:
	void SortColliders();
	void RemoveExpiredReferences();

public:
	CollisionChecker collisionChecker;

private:
	std::vector<std::weak_ptr<AABBCollider>> colliders;
};