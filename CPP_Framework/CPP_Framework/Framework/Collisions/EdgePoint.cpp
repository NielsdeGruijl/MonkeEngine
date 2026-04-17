#include "EdgePoint.h"

#include "AABBCollider.h"

EdgePoint::EdgePoint(int pColliderId, int pEdgeId, float* pPosition, bool pIsEntry)
	: colliderId(pColliderId), edgeId(pEdgeId), position(pPosition), isEntry(pIsEntry)
{
}
