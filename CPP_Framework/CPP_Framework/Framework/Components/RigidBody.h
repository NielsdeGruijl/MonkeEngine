#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Collisions/AABBCollider.h"	

struct Collision;

class RigidBody : public Component
{
public:
	std::shared_ptr<AABBCollider> collider;

	enum VelocityType
	{
		continuous,
		instant,
		velocityChange
	};

	Vector2 velocity;

	float mass = 1;
	float drag = 1;
	float gravity = 1;
	float friction;
	float bounciness;

	bool isGrounded;

public:
	RigidBody(float pDrag = 1, float pGravity = 1, float pFriction = 1, float pBounciness = 0);
	~RigidBody();

	void OnLoad() override;

	void Update() override;

	void SetVelocity(Vector2 pVelocity);
	void AddForce(Vector2 pVelocity, VelocityType pVelocityType = continuous);

	void HandleCollision(Collision collision);

private:
	Vector2 dragForce;
	Vector2 gravityForce;

private:
	void Move();
	void CalculateDrag();
	void ApplyGravity();
};