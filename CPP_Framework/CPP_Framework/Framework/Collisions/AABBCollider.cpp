#include <iostream>

#include "../Objects/Object.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Object* pObject, Vector2 pSize, Vector2* pPosition)
	: Component(pObject)
{
	size = pSize;
	radius = pSize * 0.5f;
	position = &pObject->position;

	isTrigger = false;

	currentCollisionState = exit;
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::Update()
{
	Component::Update();

	left = position->x - radius.x;
	right = position->x + radius.x;
	top = position->y - radius.y;
	bottom = position->y + radius.y;
	
	//std::cout << object->GetID() << " collider position: " << position->x << "\n";
	//std::cout << object->GetID() << " collider right: " << right << "\n";
}

void AABBCollider::UpdateBounds()
{
	left = position->x - radius.x;
	right = position->x + radius.x;
	top = position->y - radius.y;
	bottom = position->y + radius.y;
}

bool AABBCollider::CheckCollision(std::shared_ptr<AABBCollider> pCollider)
{
	UpdateBounds();
	pCollider->UpdateBounds();

	float topDiff = top - pCollider->bottom;
	float bottomDiff = bottom - pCollider->top;
	float leftDiff = left - pCollider->right;
	float rightDiff = right - pCollider->left;
	Vector2 totalSize = size + pCollider->size;

	float rightDistance = pCollider->left - right;

	//if (abs(topDiff) < totalSize.y && abs(bottomDiff) < totalSize.y)
	//{
	//	if (leftDiff < -0.01f && rightDiff > 0)
	//	{
	//		if (currentCollisionState != exit)
	//			SetCollisionState(pCollider, stay);
	//		
	//		if (currentCollisionState == exit)
	//			SetCollisionState(pCollider, enter);
	//		
	//		return true;
	//	}
	//	if (abs(leftDiff) <= 1 || abs(rightDiff) <= 1)
	//	{
	//		if (currentCollisionState != exit)
	//			SetCollisionState(pCollider, stay);
	//		
	//		return false;
	//	}
	//}
	//if (abs(leftDiff) < totalSize.x && abs(rightDiff) < totalSize.x)
	//{
	//	if (topDiff < 0 && bottomDiff > 0)
	//	{
	//		if (currentCollisionState != exit)
	//			SetCollisionState(pCollider, stay);
	//		
	//		if (currentCollisionState == exit)
	//			SetCollisionState(pCollider, enter);
	//		
	//		return true;
	//	}
	//	if (abs(topDiff) <= 1 || abs(bottomDiff) <= 1)
	//	{
	//		if (currentCollisionState != exit)
	//			SetCollisionState(pCollider, stay);
	//		return false;
	//	}
	//}

	if (rightDistance < 0)
	{
		if (topDiff < 0 && bottomDiff > 0)
		{
			if (currentCollisionState != exit)
				SetCollisionState(pCollider, stay);

			if (currentCollisionState == exit)
				SetCollisionState(pCollider, enter);

			return true;
		}
		if (abs(topDiff) < 0.1f || abs(bottomDiff) < 0.1f)
		{
			if (currentCollisionState != exit)
				SetCollisionState(pCollider, stay);

			return false;
		}
	}
	
	if (currentCollisionState != exit)
		SetCollisionState(pCollider, exit);

	return false;
}

void AABBCollider::SetCollisionState(std::shared_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState)
{
	currentCollisionState = pCollisionState;
	pOtherCollider->currentCollisionState = pCollisionState;

	switch (pCollisionState)
	{
	case enter:
		collisionEnterEvent.Invoke();
		pOtherCollider->collisionEnterEvent.Invoke();
		break;
	case stay:
		collisionStayEvent.Invoke();
		pOtherCollider->collisionStayEvent.Invoke();
		break;
	case exit:
		collisionExitEvent.Invoke();
		pOtherCollider->collisionExitEvent.Invoke();
		break;
	default:
		collisionExitEvent.Invoke();
		pOtherCollider->collisionExitEvent.Invoke();
		break;
	}
}