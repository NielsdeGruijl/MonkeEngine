#pragma once

#include <iostream>
#include "AABBCollider.h"

class CollisionChecker
{
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider, bool pIsPawn = false);
	void CheckCollisions();
	void CheckSweptCollisions(std::shared_ptr<AABBCollider> pCollider1);
	void DiscreteCollision(std::shared_ptr<AABBCollider> pCollider1, std::shared_ptr<AABBCollider> pCollider2);

private:
	std::vector<std::shared_ptr<AABBCollider>> pawnColliders;
	std::vector<std::shared_ptr<AABBCollider>> objectColliders;
};