#include "EdgePoint.h"
#include "CollisionChecker.h"

class TwoDimensionalSAP
{
public:
	std::vector<EdgePoint> xEdges;
	std::vector<EdgePoint> yEdges;

	std::vector<std::weak_ptr<AABBCollider>> colliders;

	std::vector<std::pair<int, int>> xCollisions;
	std::vector<std::pair<int, int>> yCollisions;

	CollisionChecker collisionChecker;

	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void Sweep();

	void SweepX();
	void SweepY();

	int colliderId;
};