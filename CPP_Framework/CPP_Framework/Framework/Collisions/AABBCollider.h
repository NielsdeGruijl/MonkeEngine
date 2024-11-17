#pragma once

#include "../Math/Vector2.h"
#include "../Components/Component.h"

class AABBCollider : public Component
{
public:
	Vector2 radius;
	Vector2 size;
	Vector2 position;

	bool isTrigger;
	bool isColliding;

	float left, right, top, bottom;

public:
	AABBCollider(Vector2 pSize, Vector2 pPosition);
	~AABBCollider();

	void Update() override;

	void SetPosition(Vector2 pPosition);
	void Move(Vector2 pVelocity);

	bool CheckCollision(std::shared_ptr<AABBCollider> pCollider);
};