#include <iostream>

#include "../Objects/Object.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Vector2 pSize, Vector2 pPosition)
{
	size = pSize;
	radius = pSize * 0.5f;
	position = pPosition;

	isTrigger = false;
	isColliding = false;
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::Update()
{
	Component::Update();
	SetPosition(object->position);
}

void AABBCollider::SetPosition(Vector2 pPosition)
{
	position = pPosition;

	left = position.x - radius.x;
	right = position.x + radius.x;
	top = position.y - radius.y;
	bottom = position.y + radius.y;
}

void AABBCollider::Move(Vector2 pVelocity)
{
	position += pVelocity;
}

bool AABBCollider::CheckCollision(std::shared_ptr<AABBCollider> pCollider)
{
	if (this->left < pCollider->right && 
		this->right > pCollider->left && 
		this->top < pCollider->bottom && 
		this->bottom > pCollider->top)
	{
		isColliding = true;
		return true;
	}
	
	if (isColliding)
		isColliding = false;

	return false;
}