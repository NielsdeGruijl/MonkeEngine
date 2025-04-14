#include <iostream>

#include "../Objects/Object.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Object* pObject, Vector2* pPosition)
	: Component(pObject)
{
	radius = Vector2(0, 0);
	position = &pObject->position;

	isTrigger = false;

	currentCollisionState = exit;
}

AABBCollider::~AABBCollider()
{
	Component::~Component();
	
	collisionEnterEvent.ClearSubscribers();
	collisionStayEvent.ClearSubscribers();
	collisionExitEvent.ClearSubscribers();
}

void AABBCollider::Update()
{
	Component::Update();
	UpdateBounds();
}

void AABBCollider::UpdateBounds()
{
	radius = object->GetSize() * 0.5f;

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
	Vector2 totalSize = object->GetSize() + pCollider->object->GetSize();

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

	if (this)
	{
		switch (pCollisionState)
		{
		case enter:
			collisionEnterEvent.Invoke();
			break;
		case stay:
			collisionStayEvent.Invoke();
			break;
		case exit:
			collisionExitEvent.Invoke();
			break;
		default:
			collisionExitEvent.Invoke();
			break;
		}
	}

	if (pOtherCollider)
	{
		switch (pCollisionState)
		{
		case enter:
			pOtherCollider->collisionEnterEvent.Invoke();
			break;
		case stay:
			pOtherCollider->collisionStayEvent.Invoke();
			break;
		case exit:
			pOtherCollider->collisionExitEvent.Invoke();
			break;
		default:
			pOtherCollider->collisionExitEvent.Invoke();
			break;
		}
	}
}