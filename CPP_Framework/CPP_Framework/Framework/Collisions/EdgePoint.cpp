#include "EdgePoint.h"

#include "AABBCollider.h"

EdgePoint::EdgePoint(int pColliderId, float* position, bool isEntry)
	: colliderId(pColliderId), position(position), isEntry(isEntry)
{
}
