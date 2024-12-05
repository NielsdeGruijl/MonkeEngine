#pragma once

#include <iostream>
#include "AABBCollider.h"
#include "../Components/RigidBody.h"

class CollisionChecker
{
public:
	float collisionCount = 0;
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider);
	void AddRigidBody(std::shared_ptr<RigidBody> pRigidBody);

	void CheckCollisions();
	void PawnToObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pOtherCollider);
	void PawnToPawnCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody);

	Vector2 CalculateCollisionTime(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider);

	Vector2 ElasticCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody);

	void CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody, Vector2 pNormal);

private:
	std::vector<std::shared_ptr<RigidBody>> rigidBodies;
	std::vector<std::shared_ptr<AABBCollider>> objectColliders;
};