#pragma once

#include <iostream>
#include <unordered_map>
#include "AABBCollider.h"
#include "../Components/RigidBody.h"

class CollisionChecker
{
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider);
	void AddRigidBody(std::shared_ptr<RigidBody> pRigidBody);

	void RemoveExpiredReferences();
	void SortColliders();

	void CheckCollisions();

	void ObjectCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<AABBCollider> pRigidBodyB);
	void RigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);

	Vector2 CalculateCollisionTime(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider);
	Vector2 CalculateCollisionDistance(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);

	Vector2 ElasticCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);

	void CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal);

private:
	std::vector<std::weak_ptr<RigidBody>> rigidBodies;
	std::vector<std::weak_ptr<AABBCollider>> objectColliders;
	int amountOfExpiredRigidBodies;
};