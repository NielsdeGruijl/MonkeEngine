#pragma once
#include <iostream>

class AABBCollider;
using std::shared_ptr;

struct EdgePoint
{
	EdgePoint(int pColliderId, float* position, bool isEntry);

	int colliderId;
	float* position;
	bool isEntry;
};