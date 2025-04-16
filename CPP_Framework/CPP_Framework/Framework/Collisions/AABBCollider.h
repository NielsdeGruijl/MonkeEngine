#pragma once

#include "../Math/Vector2.h"
#include "../Components/Component.h"
#include "../Events/Event.h"
#include "../Objects/GameObject.h"


class AABBCollider : public Component
{
public:
	Vector2* position;
	Vector2 radius;

	Event collisionEnterEvent;
	Event collisionStayEvent;
	Event collisionExitEvent;
	ParamEvent<GameObject*> paramCollisionEnterEvent;
	
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
	AABBCollider(GameObject* pObject, Vector2* pPosition);
	~AABBCollider();

	void Update() override;

	void UpdateBounds();

	bool CheckCollision(std::shared_ptr<AABBCollider> pCollider);

private:
	void SetCollisionState(std::shared_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState);
};