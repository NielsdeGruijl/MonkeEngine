#include <iostream>

#include "AABBCollider.h"

AABBCollider::AABBCollider(GameObject* pObject, Vector2* pPosition)
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

	if (rightToLeftDistance < 0 && abs(rightToLeftDistance) < totalSize.x)
	{
		if (topToBottomDistance < 0 && bottomToTopDistance > 0)
		{
			if (isTrigger || pCollider->isTrigger)
				return false;

			return true;
		}
	}

	return false;
}

bool AABBCollider::HasExitedCollision(std::shared_ptr<AABBCollider> pCollider)
{
	UpdateBounds();
	pCollider->UpdateBounds();

	float rightToLeftDistance = pCollider->left - right;
	float topToBottomDistance = top - pCollider->bottom;
	float bottomToTopDistance = bottom - pCollider->top;
	Vector2 totalSize = object->GetSize() + pCollider->object->GetSize();

	if (rightToLeftDistance > 0.5f)
	{
		//if (currentCollisionState != exit)
			return true;
	}
	if (rightToLeftDistance <= 0 && abs(rightToLeftDistance) < totalSize.x)
	{
		if (abs(topToBottomDistance) > 0.5f && abs(bottomToTopDistance) > 0.5f)
		{
			//if (currentCollisionState != exit)
				return true;
		}
	}

	std::cout << object->GetID() << ", " << pCollider->object->GetID() << " leftover\n";
	std::cout << rightToLeftDistance << "\n";
	std::cout << currentCollisionState << "\n";

	return false;
}

void AABBCollider::SetCollisionState(std::shared_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState)
{
	currentCollisionState = pCollisionState;
	pOtherCollider->currentCollisionState = pCollisionState;

	switch (pCollisionState)
	{
	case enter:
		collisionEnterEvent.Invoke(pOtherCollider->object);
		pOtherCollider->collisionEnterEvent.Invoke(object);
		break;
	case stay:
		collisionStayEvent.Invoke(pOtherCollider->object);
		pOtherCollider->collisionStayEvent.Invoke(object);
		break;
	case exit:
		collisionExitEvent.Invoke(pOtherCollider->object);
		pOtherCollider->collisionExitEvent.Invoke(object);
		break;
	default:
		collisionExitEvent.Invoke(pOtherCollider->object);
		pOtherCollider->collisionExitEvent.Invoke(object);
		break;
	}
}