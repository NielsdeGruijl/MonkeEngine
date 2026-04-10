#pragma once
#include "EdgePoint.h"
#include "CollisionChecker.h"
#include "ColliderIdContainer.h"

class TwoDimensionalSAP
{
public:
	std::vector<EdgePoint> xEdges;
	std::vector<EdgePoint> yEdges;

	std::vector<std::weak_ptr<AABBCollider>> colliders;
	std::vector<ColliderIdContainer> tColliders;
	std::vector<int> xEdgeIndexes;
	std::vector<int> yEdgeIndexes;

	std::vector<std::pair<int, int>> xCollisions;
	std::vector<std::pair<int, int>> yCollisions;

	CollisionChecker collisionChecker;

	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void Sweep(std::vector<int> pColliderIds);

	void SweepX(std::vector<int> pColliderIds);
	void SweepY(std::vector<int> pColliderIds);

	int colliderId = 0;
};

