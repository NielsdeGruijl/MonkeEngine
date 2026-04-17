#include <cmath>

#include "AABBCollider.h"

#include <complex>

#include "../Objects/GameObject.h"
#include "../Components/Component.h"

AABBCollider::AABBCollider(GameObject* pObject, Vector2* pPosition)
	: Component(pObject)
{
	radius = Vector2(0, 0);
	position = &pObject->position;

	isTrigger = false;
	isDynamic = false;

	currentCollisionState = exit;
}

AABBCollider::~AABBCollider()
{
	Component::~Component();
}

void AABBCollider::OnLoad()
{
	Component::OnLoad();
	Vector2 size = object->GetSize();
	circleRadius = 0.5f * std::sqrt(size.x * size.x + size.y * size.y);
}

void AABBCollider::Update(float deltaTime)
{
	Component::Update(deltaTime);
	UpdateBounds();
}

// Update world-space bounds for calculating overlaps
void AABBCollider::UpdateBounds()
{
	radius = object->GetSize() * 0.5f;

	left = position->x - radius.x;
	right = position->x + radius.x;
	top = position->y - radius.y;
	bottom = position->y + radius.y;
}

// Check if this collider is overlapping other collider
bool AABBCollider::CheckOverlap(std::shared_ptr<AABBCollider> pCollider)
{
	UpdateBounds();
	pCollider->UpdateBounds();

	// During the broad phase all collisions are sorted and checked from left to right
	// Therefore only the right to left distance needs to be calculated
	// There is no top to bottom sorting so we need to check both of those
	float rightToLeftDistance = pCollider->left - right;
	float topToBottomDistance = top - pCollider->bottom;
	float bottomToTopDistance = bottom - pCollider->top;
	Vector2 totalSize = object->GetSize() + pCollider->object->GetSize();

	if (isTrigger || pCollider->isTrigger)
		return false;

	if (rightToLeftDistance < 0 && std::abs(rightToLeftDistance) < totalSize.x)
	{
		if (topToBottomDistance <= 0 && bottomToTopDistance > 0)
		{
			return true;
		}
	}

	return false;
}

// Check if the other collider is sufficiently far away to "disconnect" the collision
bool AABBCollider::HasExitedCollision(std::shared_ptr<AABBCollider> pCollider)
{
	UpdateBounds();
	pCollider->UpdateBounds();

	float rightToLeftDistance = pCollider->left - right;
	float topToBottomDistance = top - pCollider->bottom;
	float bottomToTopDistance = bottom - pCollider->top;
	Vector2 totalSize = object->GetSize() + pCollider->object->GetSize();

	// if horizontally distant, no longer colliding
	if (rightToLeftDistance > 0.5f)
	{
		return true;
	}

	// if vertically distant, no longer colliding
	if (abs(topToBottomDistance) > 0.5f && abs(bottomToTopDistance) > 0.5f)
	{
		return true;
	}

	return false;
}

// Invoke collision events for the owning object based on the current collision state
void AABBCollider::SetCollisionState(std::weak_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState)
{
	currentCollisionState = pCollisionState;

	switch (pCollisionState)
	{
	case enter:
		collisionEnterEvent.Invoke(pOtherCollider);
		break;
	case stay:
		collisionStayEvent.Invoke(pOtherCollider);
		break;
	case exit:
		collisionExitEvent.Invoke(pOtherCollider);
		break;
	default:
		collisionExitEvent.Invoke(pOtherCollider);
		break;
	}
}