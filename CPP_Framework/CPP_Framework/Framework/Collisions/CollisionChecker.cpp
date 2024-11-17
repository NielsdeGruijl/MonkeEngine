#include "CollisionChecker.h"

#include "../Objects/Pawn.h"

#include "../Components/SpriteRenderer.h"
#include "../Components/RigidBody.h"

#include "../Math/Timer.h"

#include "Collision.h"

extern float deltaTime;

void CollisionChecker::AddCollider(std::shared_ptr<AABBCollider> pCollider)
{
	objectColliders.push_back(pCollider);
}

void CollisionChecker::AddRigidBody(std::shared_ptr<RigidBody> pRigidBody)
{
	rigidBodies.push_back(pRigidBody);
}

void CollisionChecker::CheckCollisions()
{
	for (size_t i = 0; i < rigidBodies.size(); i++)
	{
		//for (size_t j = 0; j < objectColliders.size(); j++)
		//{
		//	if (rigidBodies[i]->collider == objectColliders[j])
		//		continue;

		//	if (rigidBodies[i]->collider->CheckCollision(objectColliders[j]))
		//		PawnToObjectCollision(rigidBodies[i], objectColliders[j]);
		//}

		for (size_t j = i + 1; j < rigidBodies.size(); j++)
		{
			if (rigidBodies[i] == rigidBodies[j])
				continue;

			if (rigidBodies[i]->collider->CheckCollision(rigidBodies[j]->collider))
				PawnToPawnCollision(rigidBodies[i], rigidBodies[j]);
		}
	}
}

void CollisionChecker::PawnToObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider)
{
	Vector2 collisionTime = CalculateCollisionTime(pRigidBody, pObjectCollider);
	Vector2 normal(0, 0);

	if (collisionTime.x > collisionTime.y)
	{
		if (pRigidBody->velocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);
	}
	else
	{
		if(pRigidBody->velocity.y > 0)
			normal = Vector2(0, -1);
		else
			normal = Vector2(0, 1);
	}

	float shortestCollisionTime = std::max<float>(collisionTime.x, collisionTime.y);

	if (shortestCollisionTime >= -1)
	{
		Object* object = pObjectCollider->GetObject();
		pRigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime));
	}
}

void CollisionChecker::PawnToPawnCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody)
{
	Vector2 collisionTime = CalculateCollisionTime(pRigidBody, pOtherRigidBody->collider);
	Vector2 otherCollisionTime = CalculateCollisionTime(pOtherRigidBody, pRigidBody->collider);

	float shortestCollisionTime = std::max<float>(collisionTime.x, collisionTime.y);
	float otherShortestCollisionTime = std::max<float>(otherCollisionTime.x, otherCollisionTime.y);

	Vector2 normal;


	if (shortestCollisionTime > otherShortestCollisionTime)
	{
		if (shortestCollisionTime < -1)
			return;

		Vector2 diff = pRigidBody->velocity - pOtherRigidBody->velocity;

		Object* object = pOtherRigidBody->GetObject();
		pRigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime));
	}
	else
	{
		if (otherShortestCollisionTime < -1)
			return;

		Object* object = pRigidBody->GetObject();
		pOtherRigidBody->HandleCollision(Collision(object, normal, otherShortestCollisionTime));
	}
}

Vector2 CollisionChecker::CalculateCollisionTime(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider)
{
	std::shared_ptr<AABBCollider> controllerCollider = pRigidBody->collider;
	Vector2 pawnVelocity = pRigidBody->velocity;
	float xCollisionEntry, yCollisionEntry;
	float xCollisionTime, yCollisionTime;

	if (pawnVelocity.x != 0)
	{
		if (pawnVelocity.x > 0)
			xCollisionEntry = pObjectCollider->left - controllerCollider->right;
		else
			xCollisionEntry = pObjectCollider->right - controllerCollider->left;

		xCollisionTime = xCollisionEntry / pawnVelocity.x;
	}
	else
	{
		xCollisionEntry = -std::numeric_limits<float>::infinity();
		xCollisionTime = -std::numeric_limits<float>::infinity();
	}

	if (pawnVelocity.y != 0)
	{
		if (pawnVelocity.y > 0)
			yCollisionEntry = pObjectCollider->top - controllerCollider->bottom;
		else
			yCollisionEntry = pObjectCollider->bottom - controllerCollider->top;

		yCollisionTime = yCollisionEntry / pawnVelocity.y;
	}
	else
	{
		yCollisionEntry = -std::numeric_limits<float>::infinity();
		yCollisionTime = -std::numeric_limits<float>::infinity();
	}

	return Vector2(xCollisionTime, yCollisionTime);
}

// Clean up DiscreteCollision function and make it pretty :)
// 
// Implement continuous collision detection
//
// Create a better normal calculation