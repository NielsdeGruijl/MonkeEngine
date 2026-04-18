#include "EdgePoint.h"

#include "AABBCollider.h"

EdgePoint::EdgePoint()
	: colliderId(0), edgeId(0), position(nullptr), isEntry(false)
{
}

EdgePoint::EdgePoint(int pColliderId, int pEdgeId, float* pPosition, bool pIsEntry)
	: colliderId(pColliderId), edgeId(pEdgeId), position(pPosition), isEntry(pIsEntry)
{
}
