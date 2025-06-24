#pragma once
#include "AABBCollider.h"

class SpatialNode
{
public:
	Vector2 minBounds;
	Vector2 maxBounds;

	std::vector<std::weak_ptr<AABBCollider>> colliders;

	SpatialNode(Vector2 pPosition, Vector2 pSize);

	bool operator==(SpatialNode other);
	bool operator==(SpatialNode* other);
};