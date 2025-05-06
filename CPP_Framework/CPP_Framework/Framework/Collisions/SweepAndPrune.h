#include "CollisionChecker.h"
#include "AABBCollider.h"
#include "../Components/RigidBody.h"
#include "EdgePoint.h"


class SweepAndPrune
{
public:
	void Sweep();
	void Prune(int pColliderId);
	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void SortEdgePoints();
	void RemoveTouchingCollider(int pColliderId);

public:
	CollisionChecker collisionChecker;
private:
	std::vector<EdgePoint> edgePoints;
	std::vector<std::weak_ptr<AABBCollider>> colliders;
	std::vector<int> touchingColliders;

	int colliderId;
};