#pragma once
#include <iostream>
#include <memory>

class AABBCollider;
using std::shared_ptr;

struct EdgePoint
{
	EdgePoint();
	EdgePoint(int pColliderId, int pEdgeId, float* pPosition, bool pIsEntry);

	int colliderId;
	int edgeId;
	float* position;
	bool isEntry;
};