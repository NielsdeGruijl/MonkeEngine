#include "CollisionChecker.h"

void CollisionChecker::AddCollider(AABBCollider* pCollider, bool pIsPawn)
{
	if (pIsPawn)
		pawnColliders.push_back(pCollider);
	else
		objectColliders.push_back(pCollider);
}

void CollisionChecker::CheckCollisions()
{
	for (AABBCollider* pawnCollider : pawnColliders)
	{
		for (AABBCollider* objectCollider : objectColliders)
		{
			if (pawnCollider->CheckCollision(objectCollider))
				HandleCollision(pawnCollider, objectCollider);
		}
	}
}

void CollisionChecker::HandleCollision(AABBCollider* pCollider1, AABBCollider* pCollider2)
{
	std::cout << "Collision detected! \n";
}
