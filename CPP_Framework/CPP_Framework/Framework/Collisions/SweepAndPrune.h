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
	std::vector<EdgePoint> edgePoints;
	std::vector<std::weak_ptr<AABBCollider>> colliders;
	std::vector<ColliderIdContainer> tColliders;
	std::vector<int> touchingColliders;
	std::vector<int> xEdgeIndexes;

	int colliderId;
};