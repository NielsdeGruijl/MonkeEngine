#include "CollisionChecker.h"

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

void CollisionChecker::RemoveExpiredReferences()
{
	for (std::weak_ptr<RigidBody> rigidBody : rigidBodies)
	{
		if (rigidBody.expired())
			amountOfExpiredRigidBodies++;
	}
	
	while (amountOfExpiredRigidBodies > 0)
	{
		rigidBodies.erase(
			std::remove_if(rigidBodies.begin(), rigidBodies.end(),
				[](std::weak_ptr<RigidBody> rb)
				{
					return rb.expired();
				}),
			rigidBodies.end());
	
		amountOfExpiredRigidBodies--;
	}
}

void CollisionChecker::SortColliders()
{
	RemoveExpiredReferences();

	std::sort(rigidBodies.begin(), rigidBodies.end(), [](std::weak_ptr<RigidBody> pRigidBodyA, std::weak_ptr<RigidBody> pRigidBodyB)
		{
			std::shared_ptr<RigidBody> rigidBodyA = pRigidBodyA.lock();
			std::shared_ptr<RigidBody> rigidBodyB = pRigidBodyB.lock();
		
			return rigidBodyA->collider->left < rigidBodyB->collider->left;
		});
	
	std::sort(objectColliders.begin(), objectColliders.end(), [](std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
		{
			std::shared_ptr<AABBCollider> colliderA = pColliderA.lock();
			std::shared_ptr<AABBCollider> colliderB = pColliderB.lock();
	
			return colliderA->left < colliderB->left;
		});
}

void CollisionChecker::AddCollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
{
	//if (auto colliderA = pColliderA.lock())
	//{
	//	if (auto colliderB = pColliderB.lock())
	//	{
	//		for (size_t i = 0; i < collisionPairs.size(); i++)
	//		{
	//			if (collisionPairs[i]->DoesCollisionPairExist(colliderA, colliderB))
	//				return;
	//		}

	//		if (colliderA->CheckCollision(colliderB))
	//			collisionPairs.push_back(new CollisionPair(colliderA, colliderB));
	//	}
	//}

	//std::cout << collisionPairs.size() << "\n";
}

void CollisionChecker::AddCollisionPair(CollisionPair pCollisionPair)
{
	for (size_t i = 0; i < collisionPairs.size(); i++)
	{
		if (collisionPairs[i] == pCollisionPair)
			return;
	}

	if (auto colliderA = pCollisionPair.colliderA.lock())
	{
		if (auto colliderB = pCollisionPair.colliderB.lock())
		{
			if (colliderA->CheckCollision(colliderB))
			{
				collisionPairs.push_back(pCollisionPair);
				pCollisionPair.OnEnter();
			}
		}
	}
}

void CollisionChecker::CheckCollisionPairs()
{
	if (collisionPairs.size() <= 0)
		return;

	for (size_t i = 0; i < collisionPairs.size(); i++)
	{
		CheckCollision(collisionPairs[i]);
	}
}

//void CollisionChecker::CheckCollisions()
//{
//	SortColliders();
//
//	for (size_t i = 0; i < rigidBodies.size(); i++)
//	{
//		// Rigidbody vs static objects
//		for (size_t j = 0; j < objectColliders.size(); j++)
//		{
//			if (auto rigidBodyA = rigidBodies[i].lock())
//			{
//				if (auto collider = objectColliders[j].lock())
//				{
//					if (rigidBodyA->collider->CheckCollision(collider))
//					{
//						//ObjectCollision(rigidBodyA, collider);
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//			else
//			{
//				break;
//			}
//		}
//		
//		// Rigidbody vs other rigidbody
//		for (size_t j = i + 1; j < rigidBodies.size(); j++)
//		{
//			if (auto rigidBodyA = rigidBodies[i].lock())
//			{
//				if (auto rigidBodyB = rigidBodies[j].lock())
//				{
//					if (rigidBodyA == rigidBodyB)
//						continue;
//			
//					if (rigidBodyB->collider->left > rigidBodyA->collider->right + 1)
//						break;
//			
//					if (rigidBodyA->collider->CheckCollision(rigidBodyB->collider))
//					{
//						RigidBodyCollision(rigidBodyA, rigidBodyB);
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//}

//void CollisionChecker::CheckCollision(std::weak_ptr<AABBCollider> pCollider, std::weak_ptr<AABBCollider> pColliderB)
//{
//	std::shared_ptr<AABBCollider> colliderA = pCollider.lock();
//	std::shared_ptr<AABBCollider> colliderB = pColliderB.lock();
//
//	if (colliderA->CheckCollision(colliderB))
//	{
//		std::shared_ptr<RigidBody> rigidBodyA, rigidBodyB;
//		if (colliderA->object->TryGetComponent<RigidBody>(rigidBodyA))
//		{
//			if (colliderB->object->TryGetComponent<RigidBody>(rigidBodyB))
//			{
//				RigidBodyCollision(rigidBodyA, rigidBodyB);
//				return;
//			}
//			ObjectCollision(rigidBodyA, colliderB);
//			return;
//		}
//		else
//		{
//			ObjectCollision(colliderA, colliderB->object->GetComponent<RigidBody>());
//		}
//	}
//}

void CollisionChecker::CheckCollision(CollisionPair pCollisionPair)
{
	std::shared_ptr<AABBCollider> colliderA = pCollisionPair.colliderA.lock();
	std::shared_ptr<AABBCollider> colliderB = pCollisionPair.colliderB.lock();

	//std::cout << " ==============================\n";

	if (colliderA->CheckCollision(colliderB))
	{
		std::shared_ptr<RigidBody> rigidBodyA, rigidBodyB;
		if (colliderA->object->TryGetComponent<RigidBody>(rigidBodyA))
		{
			if (colliderB->object->TryGetComponent<RigidBody>(rigidBodyB))
			{
				RigidBodyCollision(rigidBodyA, rigidBodyB);
			}
			else
			{
				ObjectCollision(rigidBodyA, colliderB);
			}
		}
		else
		{
			ObjectCollision(colliderA, colliderB->object->GetComponent<RigidBody>());
		}
	}
	else if (colliderA->HasExitedCollision(colliderB))
	{
		auto it = std::find(collisionPairs.begin(), collisionPairs.end(), pCollisionPair);
		collisionPairs.erase(it);
		return;
	}
}

void CollisionChecker::ObjectCollision(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pCollider)
{
	Vector2 collisionDistance = CalculateCollisionDistance(pRigidBody->collider, pCollider);
	Vector2 normal;

	float shortestCollisionDistance = 0;
	if (collisionDistance.x > collisionDistance.y)
	{
		if (pRigidBody->velocity.x < 0)
			return;
	
		normal = Vector2(1, 0);
	
		shortestCollisionDistance = collisionDistance.x;
	}
	else
	{
		if (pRigidBody->collider->top < pCollider->top)
		{
			if (pRigidBody->velocity.y < 0)
				return;
	
			normal = Vector2(0, -1);
		}
		else
		{
			if (pRigidBody->velocity.y > 0)
				return;
	
			normal = Vector2(0, 1);
		}
	
		shortestCollisionDistance = collisionDistance.y;
	}
	
	pRigidBody->HandleCollision(Collision(pCollider->object, normal, std::move(shortestCollisionDistance)));
}

void CollisionChecker::ObjectCollision(std::shared_ptr<AABBCollider> pCollider, std::shared_ptr<RigidBody> pRigidBody)
{
	Vector2 collisionDistance = CalculateCollisionDistance(pCollider, pRigidBody->collider);
	Vector2 normal;

	float shortestCollisionDistance = 0;
	if (collisionDistance.x > collisionDistance.y)
	{
		if (pRigidBody->velocity.x > 0)
			return;
		
		normal = Vector2(1, 0);

		shortestCollisionDistance = collisionDistance.x;
	}
	else
	{
		if (pRigidBody->collider->top < pCollider->top)
		{
			if (pRigidBody->velocity.y < 0)
				return;

			normal = Vector2(0, -1);
		}
		else
		{
			if (pRigidBody->velocity.y > 0)
				return;

			normal = Vector2(0, 1);
		}

		shortestCollisionDistance = collisionDistance.y;
	}

	pRigidBody->HandleCollision(Collision(pCollider->object, normal, std::move(shortestCollisionDistance)));
}

void CollisionChecker::RigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB)
{
	Vector2 collisionDistance = CalculateCollisionDistance(pRigidBodyA->collider, pRigidBodyB->collider);

	if (collisionDistance.x > collisionDistance.y)
	{
		if (pRigidBodyA->velocity.x == 0 && pRigidBodyB->velocity.x == 0)
			return;
		else
			HorizontalRigidBodyCollision(pRigidBodyA, pRigidBodyB, collisionDistance.x);
	}
	else
	{
		if (pRigidBodyA->velocity.y == 0 && pRigidBodyB->velocity.y == 0)
			return;
		else
			VerticalRigidBodyCollision(pRigidBodyA, pRigidBodyB, collisionDistance.y);
	}
}

void CollisionChecker::HorizontalRigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, float pCollisionDistance)
{
	Vector2 normal, otherNormal;

	if (pRigidBodyB->velocity.x > pRigidBodyA->velocity.x)
		return;

	if (pRigidBodyA->velocity.x > 0)
		normal = Vector2(-1, 0);
	else
		normal = Vector2(1, 0);

	otherNormal = normal * -1;

	float totalVelocity = abs(pRigidBodyA->velocity.x) + abs(pRigidBodyB->velocity.x);

	float aVelocityX = pRigidBodyA->velocity.x;
	float velocityPercentageA = 0;
	if (pRigidBodyA->velocity.x != 0)
		velocityPercentageA = aVelocityX / totalVelocity;
	float velocityAdjustmentA = 0.0f;


	if (velocityPercentageA != 0)
	{
		velocityAdjustmentA = pCollisionDistance * velocityPercentageA;
		velocityAdjustmentA = abs(velocityAdjustmentA) * normal.x;
	}
	else
	{
		velocityAdjustmentA = 0;
	}

	float velocityPercentageB = 0;
	float bVelocityX = pRigidBodyB->velocity.x;

	if (pRigidBodyB->velocity.x != 0)
		velocityPercentageB = bVelocityX / totalVelocity;

	float velocityAdjustmentB = 0.0f;

	if (velocityPercentageB != 0)
	{
		velocityAdjustmentB = pCollisionDistance * velocityPercentageB;
		velocityAdjustmentB = abs(velocityAdjustmentB) * otherNormal.x;
	}
	else
	{
		velocityAdjustmentB = 0;
	}

	CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
	Collision aCollision = Collision(pRigidBodyB->object, normal, velocityAdjustmentA);
	//pRigidBodyA->HandleCollision(aCollision);
	Collision bCollision = Collision(pRigidBodyA->object, otherNormal, velocityAdjustmentB);
	//pRigidBodyB->HandleCollision(bCollision);
}

void CollisionChecker::VerticalRigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, float pCollisionDistance)
{
	Vector2 normal, otherNormal;

	std::shared_ptr<RigidBody> topRigidBody, bottomRigidBody;
	if (pRigidBodyA->collider->top < pRigidBodyB->collider->top)
	{
		if (pRigidBodyB->velocity.y > pRigidBodyA->velocity.y)
			return;

		topRigidBody = pRigidBodyA;
		bottomRigidBody = pRigidBodyB;
	}
	else
	{
		if (pRigidBodyA->velocity.y > pRigidBodyB->velocity.y)
			return;

		topRigidBody = pRigidBodyB;
		bottomRigidBody = pRigidBodyA;
	}

	if (pRigidBodyA->velocity.y > 0)
		normal = Vector2(0, -1);
	else
		normal = Vector2(0, 1);

	otherNormal = normal * -1;

	float totalVelocity = abs(topRigidBody->velocity.y) + abs(bottomRigidBody->velocity.y);
	float velocityPercentageA = topRigidBody->velocity.y / totalVelocity;
	float velocityAdjustmentA;

	if (velocityPercentageA != 0)
	{
		velocityAdjustmentA = pCollisionDistance * velocityPercentageA;
		velocityAdjustmentA = abs(velocityAdjustmentA) * normal.y;
	}
	else
	{
		velocityAdjustmentA = 0;
	}

	float velocityPercentageB = bottomRigidBody->velocity.y / totalVelocity;
	float velocityAdjustmentB;

	if (velocityPercentageB != 0)
	{
		velocityAdjustmentB = pCollisionDistance * velocityPercentageB;
		velocityAdjustmentB = abs(velocityAdjustmentB) * otherNormal.y;
	}
	else
	{
		velocityAdjustmentB = 0;
	}

	CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
	topRigidBody->HandleCollision(Collision(bottomRigidBody->object, normal, std::move(velocityAdjustmentA)));
	bottomRigidBody->HandleCollision(Collision(topRigidBody->object, otherNormal, std::move(velocityAdjustmentB)));
}

void CollisionChecker::CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal)
{
	if (pRigidBodyA->bounciness > 0 || pRigidBodyB->bounciness > 0)
	{
		//std::cout << pRigidBodyA->velocity.printVector();
		pRigidBodyA->HandleBounce(pRigidBodyB);
		//std::cout << pRigidBodyA->velocity.printVector();
		pRigidBodyB->HandleBounce(pRigidBodyA);
		return;
	}

	float totalMass = pRigidBodyA->mass + pRigidBodyB->mass;
	totalMass = 1 / totalMass;

	std::shared_ptr<RigidBody> impactingRigidBody, receivingRigidBody;

	float momentumA = pRigidBodyA->velocity.GetLength() * pRigidBodyA->mass;
	float momentumB = pRigidBodyB->velocity.GetLength() * pRigidBodyB->mass;
	
	if (momentumA > momentumB)
	{
		impactingRigidBody = pRigidBodyA;
		receivingRigidBody = pRigidBodyB;
	}
	else
	{
		impactingRigidBody = pRigidBodyB;
		receivingRigidBody = pRigidBodyA;
	}

	Vector2 aImpulse, bImpulse;

	if (pNormal.x == 0)
	{
		float xVelocity = (impactingRigidBody->velocity.x * (0.4f / receivingRigidBody->mass) - receivingRigidBody->velocity.x) * totalMass;
		float yVelocity = (impactingRigidBody->velocity.y - receivingRigidBody->velocity.y) * totalMass;
	
		bImpulse = Vector2(xVelocity, yVelocity);
		aImpulse = Vector2(xVelocity, yVelocity * receivingRigidBody->mass) * -1;
	}
	if (pNormal.y == 0)
	{
		float xVelocityDifference = (impactingRigidBody->velocity.x - receivingRigidBody->velocity.x) * totalMass;
		float yVelocity = (impactingRigidBody->velocity.y * (0.4f / receivingRigidBody->mass) - receivingRigidBody->velocity.y) * totalMass;
	
		bImpulse = Vector2(xVelocityDifference, yVelocity);
		aImpulse = Vector2(xVelocityDifference * receivingRigidBody->mass, yVelocity) * -1;
	}
	
	impactingRigidBody->AddForce(aImpulse, RigidBody::instant);
	receivingRigidBody->AddForce(bImpulse, RigidBody::instant);
}	

Vector2 CollisionChecker::CalculateCollisionDistance(std::shared_ptr<AABBCollider> pColliderA, std::shared_ptr<AABBCollider> pColliderB)
{
	float xCollisionDistance = pColliderB->left - pColliderA->right;
	float yCollisionDistance = 0;

	if (pColliderA->top < pColliderB->top)
		yCollisionDistance = pColliderB->top - pColliderA->bottom;
	else
		yCollisionDistance = pColliderA->top - pColliderB->bottom;

	return Vector2(xCollisionDistance, yCollisionDistance);
}

//Vector2 CollisionChecker::ElasticCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB)
//{
//	float mass1 = pRigidBodyA->mass;
//	float mass2 = pRigidBodyB->mass;
//	
//	std::shared_ptr<AABBCollider> col1 = pRigidBodyA->collider;
//	std::shared_ptr<AABBCollider> col2 = pRigidBodyB->collider;
//	
//	Vector2 v1 = pRigidBodyA->velocity;
//	Vector2 v2 = pRigidBodyB->velocity;
//	
//	Vector2 normal = Vector2(col2->position->x - col1->position->x, col2->position->y - col1->position->y);
//	normal.Normalize();
//	Vector2 tangent = Vector2(-normal.y, normal.x);
//	
//	float v1n, v1t, v2n, v2t;
//	
//	v1n = v1.Dot(normal);
//	v1t = v1.Dot(tangent);
//	v2n = v2.Dot(normal);
//	v2t = v2.Dot(tangent);
//	
//	float v1np = ((v1n * (mass1 - mass2)) + (2 * mass2 * v2n)) / (mass1 + mass2);
//	float v2np = ((v2n * (mass2 - mass1)) + (2 * mass1 * v1n)) / (mass1 + mass2);
//	
//	Vector2 v1p = (normal * v1np) + (tangent * v1t);
//	Vector2 v2p = (normal * v2np) + (tangent * v2t);
//	
//	pRigidBodyA->AddForce(v1p, RigidBody::velocityChange);
//	pRigidBodyB->AddForce(v2p, RigidBody::velocityChange);
//	
//	return Vector2();
//}