#pragma once
#include "EdgePoint.h"
#include "CollisionChecker.h"
#include "ColliderIdContainer.h"

class TwoDimensionalSAP
{
public:
	// Links collider id to its edge ids
	std::unordered_map<int, std::pair<int, int>> edgeMap;

	std::unordered_map<int, EdgePoint> xEdgeIdMap;
	std::unordered_map<int, EdgePoint> yEdgeIdMap;

	//std::vector<std::weak_ptr<AABBCollider>> colliders;
	std::unordered_map<int, std::weak_ptr<AABBCollider>> colliders;
	std::vector<ColliderIdContainer> tColliders;
	std::vector<int> xEdgeIndexes;
	std::vector<int> yEdgeIndexes;

	std::vector<std::pair<int, int>> xCollisions;
	std::vector<std::pair<int, int>> yCollisions;

	CollisionChecker collisionChecker;

	void RemoveExpiredReferences();

	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void Sweep(std::vector<int> pColliderIds);

	void SweepX(std::vector<int> pColliderIds);
	void SweepY(std::vector<int> pColliderIds);

	int colliderId = 0;
	int edgeId = 0;
};

