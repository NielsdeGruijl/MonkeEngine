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

void CollisionChecker::CheckCollisions()
{
	SortColliders();

	for (size_t i = 0; i < rigidBodies.size(); i++)
	{
		// Rigidbody vs static objects
		for (size_t j = 0; j < objectColliders.size(); j++)
		{
			if (auto rigidBodyA = rigidBodies[i].lock())
			{
				if (auto collider = objectColliders[j].lock())
				{
					if (rigidBodyA->collider->CheckCollision(collider))
					{
						//ObjectCollision(rigidBodyA, collider);
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
		
		// Rigidbody vs other rigidbody
		for (size_t j = i + 1; j < rigidBodies.size(); j++)
		{
			if (auto rigidBodyA = rigidBodies[i].lock())
			{
				if (auto rigidBodyB = rigidBodies[j].lock())
				{
					if (rigidBodyA == rigidBodyB)
						continue;
			
					if (rigidBodyB->collider->left > rigidBodyA->collider->right + 1)
						break;
			
					if (rigidBodyA->collider->CheckCollision(rigidBodyB->collider))
					{
						RigidBodyCollision(rigidBodyA, rigidBodyB);
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
	}
}

void CollisionChecker::CheckCollision(std::weak_ptr<AABBCollider> pCollider, std::weak_ptr<AABBCollider> pColliderB)
{
	std::shared_ptr<AABBCollider> colliderA = pCollider.lock();
	std::shared_ptr<AABBCollider> colliderB = pColliderB.lock();

	if (colliderA->CheckCollision(colliderB))
	{
		std::shared_ptr<RigidBody> rigidBodyA, rigidBodyB;
		if (colliderA->object->TryGetComponent<RigidBody>(rigidBodyA))
		{
			if (colliderB->object->TryGetComponent<RigidBody>(rigidBodyB))
			{
				RigidBodyCollision(rigidBodyA, rigidBodyB);
				return;
			}
			ObjectCollision(colliderA, colliderB, true);
			return;
		}
		else
		{
			ObjectCollision(colliderA, colliderB, false);
		}
	}
}

void CollisionChecker::ObjectCollision(std::shared_ptr<AABBCollider> pColliderA, std::shared_ptr<AABBCollider> pColliderB, bool pIsColliderADynamic)
{
	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<AABBCollider> collider;
	Vector2 collisionTime = CalculateCollisionDistance(pColliderA, pColliderB);
	Vector2 normal;

	if (pIsColliderADynamic)
	{
		rigidBody = pColliderA->object->GetComponent<RigidBody>();
		collider = pColliderB;
	}
	else
	{
		collider = pColliderA;
		rigidBody = pColliderB->object->GetComponent<RigidBody>();
	}

	if (collisionTime.x > collisionTime.y)
	{
		if (rigidBody->velocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);
	}
	else
	{
		if(rigidBody->velocity.y > 0)
			normal = Vector2(0, -1);
		else
			normal = Vector2(0, 1);
	}

	float shortestCollisionTime = std::max<float>(collisionTime.x, collisionTime.y);
	GameObject* object = collider->object;
	rigidBody->HandleCollision(Collision(object, normal, shortestCollisionTime));
}

void CollisionChecker::RigidBodyCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB)
{
	Vector2 collisionDistance = CalculateCollisionDistance(pRigidBodyA->collider, pRigidBodyB->collider);

	Vector2 normal, otherNormal;

	if (collisionDistance.x > collisionDistance.y)
	{
		if (pRigidBodyB->velocity.x > pRigidBodyA->velocity.x)
			return;

		if (pRigidBodyA->velocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);

		otherNormal = normal * -1;

		float totalVelocity = abs(pRigidBodyA->velocity.x) + abs(pRigidBodyB->velocity.x);
		float velocityPercentageA = pRigidBodyA->velocity.x / totalVelocity;
		float velocityAdjustmentA;

		if (velocityPercentageA != 0)
		{
			velocityAdjustmentA = collisionDistance.x * velocityPercentageA;
			velocityAdjustmentA = abs(velocityAdjustmentA) * normal.x;
		}
		else
		{
			velocityAdjustmentA = 0;
		}

		float velocityPercentageB = pRigidBodyB->velocity.x / totalVelocity;
		float velocityAdjustmentB;

		if (velocityPercentageB != 0)
		{
			velocityAdjustmentB = collisionDistance.x * velocityPercentageB;
			velocityAdjustmentB = abs(velocityAdjustmentB) * otherNormal.x;
		}
		else
		{
			velocityAdjustmentB = 0;
		}
		
		CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
		pRigidBodyA->HandleCollision(Collision(pRigidBodyB->object, normal, velocityAdjustmentA));
		pRigidBodyB->HandleCollision(Collision(pRigidBodyA->object, otherNormal, velocityAdjustmentB));
	}
	else
	{
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
			velocityAdjustmentA = collisionDistance.y * velocityPercentageA;
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
			velocityAdjustmentB = collisionDistance.y * velocityPercentageB;
			velocityAdjustmentB = abs(velocityAdjustmentB) * otherNormal.y;
		}
		else
		{
			velocityAdjustmentB = 0;
		}

		CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
		topRigidBody->HandleCollision(Collision(bottomRigidBody->object, normal, velocityAdjustmentA));
		bottomRigidBody->HandleCollision(Collision(topRigidBody->object, otherNormal, velocityAdjustmentB));
	}
}

void CollisionChecker::CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal)
{
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

Vector2 CollisionChecker::CalculateCollisionTime(std::shared_ptr<RigidBody> pRigidBody, std::shared_ptr<AABBCollider> pObjectCollider)
{
	std::shared_ptr<AABBCollider> controllerCollider = pRigidBody->collider;
	Vector2 pawnVelocity = pRigidBody->velocity;
	float xCollisionEntryDistance, yCollisionEntryDistance;

	if (pawnVelocity.x != 0)
	{
		if (pawnVelocity.x > 0)
			xCollisionEntryDistance = pObjectCollider->left - controllerCollider->right;
		else
			xCollisionEntryDistance = pObjectCollider->right - controllerCollider->left;

		if (xCollisionEntryDistance > 10 || xCollisionEntryDistance < -100)
			xCollisionEntryDistance = 0;
	}
	else
	{
		xCollisionEntryDistance = std::numeric_limits<float>::infinity();
	}

	if (pawnVelocity.y != 0)
	{
		if (pawnVelocity.y > 0)
			yCollisionEntryDistance = pObjectCollider->top - controllerCollider->bottom;
		else
			yCollisionEntryDistance = pObjectCollider->bottom - controllerCollider->top;

		if (yCollisionEntryDistance > 10 || yCollisionEntryDistance < -100)
			yCollisionEntryDistance = 0;
	}
	else
	{
		yCollisionEntryDistance = std::numeric_limits<float>::infinity();
	}

	if (xCollisionEntryDistance > 100)
	{
		std::cout << "balls\n";
	}

	return Vector2(xCollisionEntryDistance, yCollisionEntryDistance);
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

Vector2 CollisionChecker::ElasticCollision(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB)
{
	float mass1 = pRigidBodyA->mass;
	float mass2 = pRigidBodyB->mass;
	
	std::shared_ptr<AABBCollider> col1 = pRigidBodyA->collider;
	std::shared_ptr<AABBCollider> col2 = pRigidBodyB->collider;
	
	Vector2 v1 = pRigidBodyA->velocity;
	Vector2 v2 = pRigidBodyB->velocity;
	
	Vector2 normal = Vector2(col2->position->x - col1->position->x, col2->position->y - col1->position->y);
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
	
	pRigidBodyA->AddForce(v1p, RigidBody::velocityChange);
	pRigidBodyB->AddForce(v2p, RigidBody::velocityChange);
	
	return Vector2();
}