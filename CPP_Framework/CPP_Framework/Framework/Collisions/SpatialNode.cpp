#include "SpatialNode.h"

SpatialNode::SpatialNode(Vector2 pPosition, Vector2 pSize)
{
	minBounds = pPosition - pSize * 0.5f;
	maxBounds = pPosition + pSize * 0.5f;
}

bool SpatialNode::operator==(SpatialNode other)
{
	if(minBounds == other.minBounds && maxBounds == other.maxBounds)
		return true;
	
	return false;
}

bool SpatialNode::operator==(SpatialNode* other)
{
	if (minBounds == other->minBounds && maxBounds == other->maxBounds)
		return true;
}
