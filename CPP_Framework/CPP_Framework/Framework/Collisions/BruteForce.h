#pragma once
#include "AABBCollider.h"
#include "CollisionChecker.h"

class BruteForce
{
public:
	void RegisterCollider(std::weak_ptr<AABBCollider> pCollider);
	void CheckCollisions(std::vector<int> pColliderIndexes);

public:
	CollisionChecker collisionChecker;

private:
	std::vector<std::weak_ptr<AABBCollider>> colliders;
};