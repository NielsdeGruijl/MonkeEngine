#pragma once

#include <memory>

#include "../Math/Vector2.h"
#include "../Components/Component.h"
#include "../Events/Event.h"

class GameObject;

class AABBCollider : public Component
{
public:
	Vector2* position;
	Vector2 radius;

	Event<GameObject*> collisionEnterEvent;
	Event<GameObject*> collisionStayEvent;
	Event<GameObject*> collisionExitEvent;
	
	enum collisionState
	{
		enter,
		stay,
		exit
	};

	collisionState currentCollisionState;

	bool isTrigger;
	bool isDynamic;

	float left, right, top, bottom;
	float circleRadius;

public:
	AABBCollider(GameObject* pObject, Vector2* pPosition);
	~AABBCollider() override;

	void OnLoad() override;
	void Update() override;

	void UpdateBounds();

	bool CheckOverlap(std::shared_ptr<AABBCollider> pCollider);
	bool HasExitedCollision(std::shared_ptr<AABBCollider> pCollider);

	void SetCollisionState(std::shared_ptr<AABBCollider> pOtherCollider, collisionState pCollisionState);
private:
};