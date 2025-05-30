#pragma once

#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Collisions/AABBCollider.h"	

class CollisionChecker;
struct Collision;

class RigidBody : public Component
{
public:
	enum VelocityType
	{
		continuous,
		instant,
		velocityChange
	};

	std::shared_ptr<AABBCollider> collider;

	Vector2 velocity;

	float mass;
	float drag;
	float gravity;
	float friction;
	float bounciness;

	bool isGrounded;

	bool xConstraint, yConstraint;

public:
	RigidBody(GameObject* pObject);
	~RigidBody();

	void OnLoad() override;

	void Update() override;

	void AddForce(Vector2 pVelocity, VelocityType pVelocityType = continuous);

	void HandleCollision(Collision collision);
	void HandleBounce(std::shared_ptr<RigidBody> pRigidBody);

private:
	Vector2 dragForce;
	Vector2 gravityForce;

private:
	void Move();
	void CalculateDrag();
	void ApplyGravity();
};