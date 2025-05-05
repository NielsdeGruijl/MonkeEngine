#include "EdgePoint.h"
#include "CollisionChecker.h"

class TwoDimensionalSAP
{
public:
	std::vector<EdgePoint> xEdges;
	std::vector<EdgePoint> yEdges;

	CollisionChecker collisionChecker;

	std::vector<CollisionPair> xPossibleCollisions;
	std::vector<CollisionPair> yPossibleCollisions;

	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void Sweep();

	void SweepX();
	void SweepY();
};