#include "AABBCollider.h"

#include <iostream>

//AABBCollider::AABBCollider()
//{
//	radius = Vector2(0, 0);
//}

//AABBCollider::AABBCollider(GameObject* pGameObject)
//	: Component(pGameObject)
//{
//	isTrigger = false;
//}

AABBCollider::AABBCollider(Vector2 pSize, Vector2 pPosition)
{
	radius = pSize * 0.5f;
	position = pPosition;
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::Update()
{
	Component::Update();
}

void AABBCollider::SetPosition(Vector2 pPosition)
{
	position = pPosition;
}

void AABBCollider::Move(Vector2 pVelocity)
{
	position += pVelocity;
}

bool AABBCollider::CheckCollision(AABBCollider* pCollider)
{
	if (abs(position.x - pCollider->position.x) > radius.x + pCollider->radius.x)
	{
		//std::cout << abs(position.x - pCollider->position.x) << "\n";
		return false;
	}
	if (abs(position.y - pCollider->position.y) > radius.y + pCollider->radius.y)
		return false;
	
	return true;
}

bool AABBCollider::CheckCollision(std::shared_ptr<AABBCollider> pCollider)
{
	if (abs(position.x - pCollider->position.x) > radius.x + pCollider->radius.x)
	{
		//std::cout << abs(position.x - pCollider->position.x) << "\n";
		return false;
	}
	if (abs(position.y - pCollider->position.y) > radius.y + pCollider->radius.y)
		return false;

	return true;
}