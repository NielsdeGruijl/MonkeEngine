#pragma once
#include <iostream>

class AABBCollider;
using std::shared_ptr;

struct EdgePoint
{
	EdgePoint(std::shared_ptr<AABBCollider> pCollider, bool pIsLeft);
	EdgePoint(std::shared_ptr<AABBCollider> pCollider, float* pPosition, bool pIsLeft);
	EdgePoint(int pColliderId, float* position, bool isEntry);

	std::weak_ptr<AABBCollider> collider;
	int colliderId;
	float* position;
	bool isLeft;
};