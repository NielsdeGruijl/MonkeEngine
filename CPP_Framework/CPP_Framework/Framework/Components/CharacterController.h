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

	float drag;
	float gravity;

public:
	CharacterController(float pDrag, float pGravity);
	~CharacterController();

	void Update() override;

	void SetVelocity(Vector2 pVelocity);
	void AddVelocity(Vector2 pVelocity, VelocityType pVelocityType = continuous);

private:
	Vector2 velocity;

private:
	void Move();
	void ApplyDrag();
	void ApplyGravity();
};