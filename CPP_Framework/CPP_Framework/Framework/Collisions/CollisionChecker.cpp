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
			{
				PawnToPawnCollision(rigidBodies[i], rigidBodies[j]);
			}
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
	Vector2 normal;
	Vector2 otherNormal;
	Vector2 collisionTime = CalculateCollisionTime(pRigidBody, pOtherRigidBody->collider);
	Vector2 otherCollisionTime = CalculateCollisionTime(pOtherRigidBody, pRigidBody->collider);
	
	float shortestCollisionTime = std::max<float>(collisionTime.x, collisionTime.y);
	float otherShortestCollisionTime = std::max<float>(otherCollisionTime.x, otherCollisionTime.y);

	//ElasticCollision(pRigidBody, pOtherRigidBody);

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

	if (otherCollisionTime.x > otherCollisionTime.y)
	{
		if (pOtherRigidBody->velocity.x > 0)
			otherNormal = Vector2(-1, 0);
		else
			otherNormal = Vector2(1, 0);
	}
	else
	{
		if (pOtherRigidBody->velocity.y > 0)
			otherNormal = Vector2(0, -1);
		else
			otherNormal = Vector2(0, 1);
	}

	//std::cout << "player : " << pOtherRigidBody->velocity.printVector();
	//std::cout << "pawn: " << pRigidBody->velocity.printVector();

	//std::cout << shortestCollisionTime << ", ";
	//std::cout << otherShortestCollisionTime << "\n";

	if (shortestCollisionTime > otherShortestCollisionTime)
	{
		if (shortestCollisionTime < -10)
			return;

		Object* object = pOtherRigidBody->GetObject();
		//if (pRigidBody->collider->currentCollisionState == pRigidBody->collider->enter)
			pRigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime));

		CollisionVelocityHandling(pRigidBody, pOtherRigidBody, normal);
	}
	else
	{
		if (otherShortestCollisionTime < -10)
			return;

		Object* object = pRigidBody->GetObject();
		//if (pRigidBody->collider->currentCollisionState == pRigidBody->collider->enter)
			pOtherRigidBody->HandleCollision(Collision(object, otherNormal, otherShortestCollisionTime));

		CollisionVelocityHandling(pOtherRigidBody, pRigidBody, otherNormal);
	}
}

void CollisionChecker::CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<RigidBody> pOtherRigidBody, Vector2 pNormal)
{
	//std::cout << pRigidBody->GetObject()->GetID() << "\n";

	float totalMass = pRigidBody->mass + pOtherRigidBody->mass;
	totalMass = 1 / totalMass;

	Vector2 normal = pOtherRigidBody->collider->position - pRigidBody->collider->position;
	normal.Normalize();

	//Vector2 velo = pRigidBody->velocity - pOtherRigidBody->velocity;
	Vector2 relativeVelocity = pNormal * (pRigidBody->velocity.GetLength() - pOtherRigidBody->velocity.GetLength());
	Vector2 impulseVelocity = relativeVelocity * -(1) * totalMass;

	std::cout << relativeVelocity.printVector();

	Vector2 aImpulse, bImpulse;

	float aMass = 1 / pRigidBody->mass;
	float bMass = 1 / pOtherRigidBody->mass;

	//if (pNormal.x == 0)
	//{
	//	aImpulse = impulseVelocity * Vector2(aMass * 0.6f, aMass * pNormal.y);
	//	bImpulse = impulseVelocity * Vector2(bMass * 0.4f, bMass * -pNormal.y);
	//}
	//if(pNormal.y == 0)
	//{
	//	aImpulse = impulseVelocity * Vector2(aMass * -pNormal.x, aMass * 0.6f);
	//	bImpulse = impulseVelocity * Vector2(bMass * -pNormal.x, bMass * 0.4f);
	//}

	aImpulse = impulseVelocity * Vector2(aMass * pNormal.x, aMass * 0.6f);
	bImpulse = impulseVelocity * Vector2(bMass * -pNormal.x, bMass * -0.4f);

	pRigidBody->AddForce(aImpulse, RigidBody::instant);
	pOtherRigidBody->AddForce(bImpulse, RigidBody::instant);

	//Vector2 tVelocity = (totalVelocity * totalMass * absNormal) + pRigidBody->velocity * Vector2(absNormal.y, absNormal.x);
	//pRigidBody->SetVelocity(tVelocity);
	//
	//float tMass = totalMass * 0.4f;
	//if (absNormal.x == 0)
	//	totalVelocity *= Vector2(tMass, totalMass);
	//if (absNormal.y == 0)
	//	totalVelocity *= Vector2(totalMass, tMass);
	//
	//pOtherRigidBody->SetVelocity(totalVelocity);
	//
	//std::cout << "==================\n";
	//std::cout << pRigidBody->velocity.printVector();
	//std::cout << pOtherRigidBody->velocity.printVector();
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

	v1n = (((mass1 - mass2) * v1n) + (2 * mass2 * v2n)) / (mass1 + mass2);
	v2n = (((mass2 - mass1) * v2n) + (2 * mass1 * v1n)) / (mass1 + mass2);

	Vector2 v1p = (normal * v1n) + (tangent * v1t);
	Vector2 v2p = (normal * v2n) + (tangent * v2t);

	pRigidBody->SetVelocity(v1p);
	pOtherRigidBody->SetVelocity(v2p);

	return Vector2();
}

// Clean up DiscreteCollision function and make it pretty :)
// 
// Implement continuous collision detection
//
// Create a better normal calculation