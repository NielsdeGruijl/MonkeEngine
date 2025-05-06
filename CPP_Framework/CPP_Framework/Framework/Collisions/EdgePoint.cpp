#include "EdgePoint.h"

#include "AABBCollider.h"

//EdgePoint::EdgePoint(std::shared_ptr<AABBCollider> pCollider, bool pIsLeft)
//	: collider(pCollider), isLeft(pIsLeft)
//{
//	if (pIsLeft)
//		position = &pCollider->left;
//	else
//		position = &pCollider->right;
//}
//
//EdgePoint::EdgePoint(std::shared_ptr<AABBCollider> pCollider, float* pPosition, bool pIsLeft)
//	: collider(pCollider), position(pPosition), isLeft(pIsLeft)
//{
//}

EdgePoint::EdgePoint(int pColliderId, float* position, bool isEntry)
	: colliderId(pColliderId), position(position), isLeft(isEntry)
{
}
