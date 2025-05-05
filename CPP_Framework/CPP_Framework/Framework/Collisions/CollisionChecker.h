#pragma once

#include <iostream>
#include <unordered_map>
#include "AABBCollider.h"
#include "CollisionPair.h"
#include "../Components/RigidBody.h"

class CollisionChecker
{
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider);
	void AddRigidBody(std::shared_ptr<RigidBody> pRigidBody);

	void RemoveExpiredReferences();
	void SortColliders();

	void AddCollisionPair(CollisionPair pCollisionPair);
	void AddCollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB);
	void CheckCollisionPairs();

	//void CheckCollisions();
	//void CheckCollision(std::weak_ptr<AABBCollider> pCollider, std::weak_ptr<AABBCollider> pColliderB);
	void CheckCollision(CollisionPair pCollisionPair);

	void ObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pCollider);
	void ObjectCollision(std::shared_ptr<AABBCollider> pCollider, std::shared_ptr<RigidBody> pRigidBody);
	void RigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);

	Vector2 CalculateCollisionDistance(std::shared_ptr<AABBCollider> pColliderA, std::shared_ptr<AABBCollider> pColliderB);
	
	void CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal);

	//Vector2 ElasticCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB);


private:
	std::vector<std::weak_ptr<RigidBody>> rigidBodies;
	std::vector<std::weak_ptr<AABBCollider>> objectColliders;
	std::vector<CollisionPair> collisionPairs;
	int amountOfExpiredRigidBodies;
};