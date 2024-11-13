#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Collisions/AABBCollider.h"	

class CharacterController : public Component
{
public:
	enum VelocityType
	{
		continuous,
		instant
	};

	Vector2 velocity;
	float drag;
	float gravity;
	float friction;

public:
	CharacterController(float pDrag, float pGravity, float pFriction);
	~CharacterController();

	void Update() override;

	void SetVelocity(Vector2 pVelocity);
	void AddVelocity(Vector2 pVelocity, VelocityType pVelocityType = continuous);

private:

private:
	void Move();
	void ApplyDrag();
	void ApplyGravity();
};