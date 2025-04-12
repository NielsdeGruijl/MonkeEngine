#include <iostream>

#include "../Objects/Object.h"
#include "AABBCollider.h"

#include "../Collisions/CollisionChecker.h"

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
	Component::~Component();
}

void AABBCollider::Update()
{
	Component::Update();
	UpdateBounds();
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

	float rightToLeftDistance = pCollider->left - right;
	float topToBottomDistance = top - pCollider->bottom;
	float bottomToTopDistance = bottom - pCollider->top;
	Vector2 totalSize = size + pCollider->size;

	if (rightToLeftDistance <= 0 && abs(rightToLeftDistance) < totalSize.x)
	{
		if (topToBottomDistance < 0 && bottomToTopDistance > 0)
		{
			if (currentCollisionState == exit)
				SetCollisionState(pCollider, enter);

			return true;
		}
		if (abs(topToBottomDistance) > 0.5f && abs(bottomToTopDistance) > 0.5f)
		{
			if (currentCollisionState != exit)
				SetCollisionState(pCollider, exit);

			return false;
		}
	}
	if (rightToLeftDistance > 0.5f)
	{
		if (currentCollisionState != exit)
			SetCollisionState(pCollider, exit);
	}

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