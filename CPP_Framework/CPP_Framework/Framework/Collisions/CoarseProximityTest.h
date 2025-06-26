#pragma once
#include "AABBCollider.h"
#include "ColliderIdContainer.h"
#include "TwoDimensionalSAP.h"
#include "SweepAndPrune.h"
#include"BruteForce.h"

class CoarseProximityTest
{
private:
	std::vector<ColliderIdContainer> colliders;
	std::vector<int> colliderIndexes;

	int colliderId = 0;

public:
	TwoDimensionalSAP* multiSweepAndPrune;
	SweepAndPrune* sweepAndPrune;
	BruteForce* bruteForce;

public:
	void MSAP();
	void SAP();
	void BruteForce();
	void RegisterCollider(std::weak_ptr<AABBCollider> pCollider);
	void SortColliders();
};