#pragma once

#include <iostream>
#include "AABBCollider.h"

class CollisionChecker
{
public:
	void AddCollider(AABBCollider* pCollider, bool pIsPawn = false);
	void CheckCollisions();
	void HandleCollision(AABBCollider* pCollider1, AABBCollider* pCollider2);
private:
	std::vector<AABBCollider*> pawnColliders;
	std::vector<AABBCollider*> objectColliders;
};