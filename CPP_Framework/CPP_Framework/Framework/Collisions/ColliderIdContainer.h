#pragma once
#include <iostream>
#include "AABBCollider.h"

struct ColliderIdContainer
{
	std::weak_ptr<AABBCollider> collider;
	int colliderId;

	ColliderIdContainer(std::weak_ptr<AABBCollider> pCollider, int pColliderId)
		: collider(pCollider), colliderId(pColliderId)
	{
	}
};
