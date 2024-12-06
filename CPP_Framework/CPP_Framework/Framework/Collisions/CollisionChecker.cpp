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
		for (size_t j = 0; j < objectColliders.size(); j++)
		{
			if (rigidBodies[i]->collider->CheckCollision(objectColliders[j]))
			{
				PawnToObjectCollision(rigidBodies[i], objectColliders[j]);
				collisionCount++;
				//std::cout << collisionCount << " object \n";
			}
		}

		for (size_t j = i + 1; j < rigidBodies.size(); j++)
		{
			if (rigidBodies[i] == rigidBodies[j])
				continue;

			if (rigidBodies[i]->collider->CheckCollision(rigidBodies[j]->collider))
			{
				PawnToPawnCollision(rigidBodies[i], rigidBodies[j]);
				collisionCount++;
				//std::cout << collisionCount << " pawn \n";
			}
		}
	}
}

void CollisionChecker::PawnToObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider)
{
	Vector2 collisionTime = CalculateCollisionTime(pRigidBody, pObjectCollider);
	Vector2 normal;

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
		Object* object = pObjectCollider->object;
		pRigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime), pRigidBody->collider->currentCollisionState);
	}
}

void CollisionChecker::PawnToPawnCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody)
{
	Vector2 normal, otherNormal;
	Vector2 collisionTime = CalculateCollisionTime(pRigidBody, pOtherRigidBody->collider);
	Vector2 otherCollisionTime = CalculateCollisionTime(pOtherRigidBody, pRigidBody->collider);

	float shortestCollisionTime = std::max<float>(collisionTime.x, collisionTime.y);
	float otherShortestCollisionTime = std::max<float>(otherCollisionTime.x, otherCollisionTime.y);

	if (collisionTime.x > collisionTime.y)
	{
		if (pRigidBody->velocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);
	}
	else
	{
		if (pRigidBody->velocity.y > 0)
			normal = Vector2(0, -1);
		else
			normal = Vector2(0, 1);
	}

	otherNormal = normal * -1;

	if (shortestCollisionTime > otherShortestCollisionTime)
	{
		if (shortestCollisionTime < -10)
			return;

		Object* object = pOtherRigidBody->object;
		pRigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime), pRigidBody->collider->currentCollisionState);

		CollisionVelocityHandling(pRigidBody, pOtherRigidBody, normal);
	}
	else
	{
		if (otherShortestCollisionTime < -10)
			return;

		Object* object = pRigidBody->object;
		pOtherRigidBody->HandleCollision(Collision(object, otherNormal, otherShortestCollisionTime), pRigidBody->collider->currentCollisionState);

		CollisionVelocityHandling(pOtherRigidBody, pRigidBody, otherNormal);
	}
}

void CollisionChecker::CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody, Vector2 pNormal)
{
	float totalMass = pRigidBody->mass + pOtherRigidBody->mass;
	totalMass = 1 / totalMass;

	Vector2 aImpulse, bImpulse;

	if (pNormal.x == 0)
	{
		float xVelocity = (pRigidBody->velocity.x * (0.4f / pOtherRigidBody->mass) - pOtherRigidBody->velocity.x) * totalMass;
		float yVelocity = (pRigidBody->velocity.y - pOtherRigidBody->velocity.y) * totalMass;

		bImpulse = Vector2(xVelocity, yVelocity);
		aImpulse = Vector2(xVelocity, yVelocity * pOtherRigidBody->mass) * -1;
	}
	if(pNormal.y == 0)
	{
		float xVelocity = (pRigidBody->velocity.x - pOtherRigidBody->velocity.x) * totalMass;
		float yVelocity = (pRigidBody->velocity.y * (0.4f / pOtherRigidBody->mass) - pOtherRigidBody->velocity.y) * totalMass;

		bImpulse = Vector2(xVelocity, yVelocity);
		aImpulse = Vector2(xVelocity * pOtherRigidBody->mass, yVelocity) * -1;
	}

	pRigidBody->AddForce(aImpulse, RigidBody::instant);
	pOtherRigidBody->AddForce(bImpulse, RigidBody::instant);
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

Vector2 CollisionChecker::ElasticCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody)
{
	float mass1 = pRigidBody->mass;
	float mass2 = pOtherRigidBody->mass;

	std::shared_ptr<AABBCollider> col1 = pRigidBody->collider;
	std::shared_ptr<AABBCollider> col2 = pOtherRigidBody->collider;

	Vector2 v1 = pRigidBody->velocity;
	Vector2 v2 = pOtherRigidBody->velocity;

	Vector2 normal = Vector2(col2->position.x - col1->position.x, col2->position.y - col1->position.y);
	normal.Normalize();
	Vector2 tangent = Vector2(-normal.y, normal.x);

	float v1n, v1t, v2n, v2t;

	v1n = v1.Dot(normal);
	v1t = v1.Dot(tangent);
	v2n = v2.Dot(normal);
	v2t = v2.Dot(tangent);

	float v1np = ((v1n * (mass1 - mass2)) + (2 * mass2 * v2n)) / (mass1 + mass2);
	float v2np = ((v2n * (mass2 - mass1)) + (2 * mass1 * v1n)) / (mass1 + mass2);

	Vector2 v1p = (normal * v1np) + (tangent * v1t);
	Vector2 v2p = (normal * v2np) + (tangent * v2t);

	pRigidBody->AddForce(v1p, RigidBody::velocityChange);
	pOtherRigidBody->AddForce(v2p, RigidBody::velocityChange);

	return Vector2();
}

// Clean up DiscreteCollision function and make it pretty :)
// 
// Implement continuous collision detection
//
// Create a better normal calculation