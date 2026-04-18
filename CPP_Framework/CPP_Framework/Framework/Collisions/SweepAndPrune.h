#pragma once
#include "CollisionChecker.h"
#include "AABBCollider.h"
#include "../Components/RigidBody.h"
#include "EdgePoint.h"
#include "ColliderIdContainer.h"

class SweepAndPrune
{
public:
	void Sweep(std::vector<int> pColliderIndexes);
	void Prune(int pColliderId);
	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void SortEdgePoints();
	void RemoveTouchingCollider(int pColliderId);

public:
	CollisionChecker collisionChecker;
private:
	std::unordered_map<int, std::pair<int, int>> edgePairs;
	std::unordered_map<int, EdgePoint> edges;
	std::unordered_map<int, std::weak_ptr<AABBCollider>> colliders;

	std::vector<EdgePoint> edgePoints;
	std::vector<int> touchingColliders;
	std::vector<int> xEdgeIndexes;

	int colliderId = 0;
	int edgeId = 0;
};