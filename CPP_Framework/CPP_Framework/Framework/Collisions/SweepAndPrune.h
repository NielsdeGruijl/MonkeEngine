#include "CollisionChecker.h"
#include "AABBCollider.h"
#include "../Components/RigidBody.h"
#include "EdgePoint.h"


class SweepAndPrune
{
public:
	void Sweep();
	void Prune(std::weak_ptr<AABBCollider> pCollider);
	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void SortEdgePoints();
	void RemoveTouchingCollider(std::weak_ptr<AABBCollider> pCollider);

public:
	CollisionChecker collisionChecker;
private:
	std::vector<EdgePoint> edgePoints;
	std::vector<std::weak_ptr<AABBCollider>> touchingColliders;
};