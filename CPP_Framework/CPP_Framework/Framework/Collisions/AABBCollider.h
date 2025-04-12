#pragma once

#include "../Math/Vector2.h"
#include "../Components/Component.h"
#include "../Events/Event.h"

class CollisionChecker;

class AABBCollider : public Component
{
public:
	CollisionChecker* collisionChecker;

	Vector2 radius;
	Vector2 size;
	Vector2* position;

	Event collisionEnterEvent;
	Event collisionStayEvent;
	Event collisionExitEvent;
	
	enum collisionState
	{
		enter,
		stay,
		exit
	};

	collisionState currentCollisionState;

	bool isTrigger;

	float left, right, top, bottom;

public:
	AABBCollider(Object* pObject, Vector2 pSize, Vector2* pPosition);
	~AABBCollider();

	void Update() override;

	void UpdateBounds();

	bool CheckCollision(std::shared_ptr<AABBCollider> pCollider);

private:
	void SetCollisionState(std::shared_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState);
};