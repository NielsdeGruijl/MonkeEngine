#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Collisions/AABBCollider.h"	
#include "../Collisions/Collision.h"

class CharacterController : public Component
{
public:
	std::shared_ptr<AABBCollider> collider;

	enum VelocityType
	{
		continuous,
		instant
	};

	Vector2 velocity;
	float drag;
	float gravity;
	float friction;
	float bounciness;

public:
	CharacterController(float pDrag = 1, float pGravity = 1, float pFriction = 1, float pBounciness = 0);
	~CharacterController();

	void OnLoad() override;

	void Update() override;

	void SetVelocity(Vector2 pVelocity);
	void AddVelocity(Vector2 pVelocity, VelocityType pVelocityType = continuous);

	void HandleCollision(Collision collision);

private:
	void Move();
	void ApplyDrag();
	void ApplyGravity();
};