#include <iostream>

#include "../Objects/Object.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Vector2 pSize, Vector2 pPosition)
{
	size = pSize;
	radius = pSize * 0.5f;
	position = pPosition;

	isTrigger = false;

	currentCollisionState = exit;
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
	float topDiff = top - pCollider->bottom;
	float bottomDiff = bottom - pCollider->top;
	float leftDiff = left - pCollider->right;
	float rightDiff = right - pCollider->left;
	Vector2 totalSize = size + pCollider->size;

	if (this->left < pCollider->right && 
		this->right > pCollider->left && 
		this->top < pCollider->bottom && 
		this->bottom > pCollider->top)
	{
	
		if (currentCollisionState == enter)
		{
			currentCollisionState = stay;
			pCollider->currentCollisionState = stay;
	
			std::cout << "stay\n";
		}
	
		if (currentCollisionState == exit)
		{
			currentCollisionState = enter;
			pCollider->currentCollisionState = enter;
	
			std::cout << "enter\n";
		}
	
		return true;
	}

	if (abs(topDiff) < totalSize.y && abs(bottomDiff) < totalSize.y)
	{
		//if (leftDiff < -0.001f || rightDiff < -0.001f)
		//{
		//	if (currentCollisionState == enter)
		//	{
		//		currentCollisionState = stay;
		//		pCollider->currentCollisionState = stay;
		//	
		//		std::cout << "stay\n";
		//	}
		//	else if (currentCollisionState == exit)
		//	{
		//		currentCollisionState = enter;
		//		pCollider->currentCollisionState = enter;
		//
		//		std::cout << "enter\n";
		//	}
		//	return true;
		//}
		if (abs(leftDiff) <= 1 || abs(rightDiff) <= 1)
		{
			if (currentCollisionState == enter)
			{
				currentCollisionState = stay;
				pCollider->currentCollisionState = stay;
		
				std::cout << "stay\n";
			}
			return false;
		}
	}
	
	if (leftDiff < totalSize.x && rightDiff < totalSize.x)
	{
		//if (topDiff < -0.01f || bottomDiff < 0.01f)
		//{
		//	if (currentCollisionState == enter)
		//	{
		//		currentCollisionState = stay;
		//		pCollider->currentCollisionState = stay;
		//	
		//		std::cout << "stay\n";
		//	}
		//	
		//	if (currentCollisionState == exit)
		//	{
		//		currentCollisionState = enter;
		//		pCollider->currentCollisionState = enter;
		//	
		//		std::cout << "enter\n";
		//	}
		//	
		//	return true;
		//}
		if (abs(topDiff) <= 1 || abs(bottomDiff) <= 1)
		{
			if (currentCollisionState == enter)
			{
				currentCollisionState = stay;
				pCollider->currentCollisionState = stay;

				std::cout << "stay\n";
			}
			return false;
		}
	}

	//if (this->left <= pCollider->right &&
	//	this->right >= pCollider->left &&
	//	this->top <= pCollider->bottom &&
	//	this->bottom >= pCollider->top)
	//{
	//	if (currentCollisionState == exit)
	//	{
	//		currentCollisionState = enter;
	//		pCollider->currentCollisionState = enter;

	//		std::cout << "enter\n";
	//	}
	//	return false;
	//}
	
	if (currentCollisionState != exit)
	{
		currentCollisionState = exit;
		pCollider->currentCollisionState = exit;

		std::cout << "exit\n";
	}

	return false;
}