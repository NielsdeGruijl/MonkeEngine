#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Objects/GameObject.h"
#include "../Collisions/AABBCollider.h"	

class CharacterController
{
public:
	enum VelocityType
	{
		continuous,
		instant
	};

	float drag;
	float gravity;

	bool useGravity;

public:
	CharacterController(GameObject* pOwner);
	~CharacterController();

	void Update();

	void SetVelocity(Vector2 pVelocity);
	void AddVelocity(Vector2 pVelocity, VelocityType pVelocityType = continuous);

private:
	GameObject* owner;
	Vector2 velocity;

private:
	void Move();
	void ApplyDrag();
	void ApplyGravity();
};