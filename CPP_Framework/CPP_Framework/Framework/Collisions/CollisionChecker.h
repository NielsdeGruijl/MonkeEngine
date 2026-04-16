#pragma once

#include <iostream>
#include <unordered_map>
#include "AABBCollider.h"
#include "CollisionPair.h"
#include "../Components/RigidBody.h"

class CollisionChecker
{
public:
	// ===== Deprecated ======
	void AddCollider(std::shared_ptr<AABBCollider> pCollider);
	void AddRigidBody(std::shared_ptr<RigidBody> pRigidBody);

	void SortColliders();
	// =======================

	void RemoveExpiredReferences();

	void AddCollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB);
	void CheckCollisionPairs();

	void CheckCollision(std::shared_ptr<CollisionPair> pCollisionPair);

	void ObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pCollider);
	void ObjectCollision(std::shared_ptr<AABBCollider> pCollider, std::shared_ptr<RigidBody> pRigidBody);

	void RigidBodyCollision(const std::shared_ptr<RigidBody> pRigidBodyA, const std::shared_ptr<RigidBody> pRigidBodyB);
	void HorizontalRigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, const std::shared_ptr<RigidBody> pRigidBodyB, float pCollisionDistance);
	void VerticalRigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, float pCollisionDistance);

	Vector2 CalculateCollisionDistance(std::shared_ptr<AABBCollider> pColliderA, std::shared_ptr<AABBCollider> pColliderB);
	
	void CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal);

	//Vector2 ElasticCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);


private:
	std::vector<std::weak_ptr<RigidBody>> rigidBodies;
	std::vector<std::weak_ptr<AABBCollider>> objectColliders;
	std::vector<std::shared_ptr<CollisionPair>> collisionPairs;
	int amountOfExpiredRigidBodies;
};