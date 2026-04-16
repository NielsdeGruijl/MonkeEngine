#include "CollisionChecker.h"

#include "../Math/Timer.h"
#include "Collision.h"

extern float deltaTime;

// ========= Deprecated =================
/*
void CollisionChecker::AddCollider(std::shared_ptr<AABBCollider> pCollider)
{
	objectColliders.push_back(pCollider);
}

void CollisionChecker::AddRigidBody(std::shared_ptr<RigidBody> pRigidBody)
{
	rigidBodies.push_back(pRigidBody);
}

// Sort colliders left to right
void CollisionChecker::SortColliders()
{

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
*/
// ===============================


// Clearing out expired collisionpairs
void CollisionChecker::RemoveExpiredReferences()
{
	// If any rigidbody in the collisionpair is expired, remove it from the collisionpair references
	std::erase_if(collisionPairs,
	              [](const std::shared_ptr<CollisionPair>& collisionPair)
	              {
		              return collisionPair->HasExpired();
	              });

	//std::cout << "rigidbody count: " << collisionPairs.size() << std::endl;
}


// Check if a collision pair already exists, if not, add it to the list.
void CollisionChecker::AddCollisionPair(std::weak_ptr<AABBCollider> pColliderA, std::weak_ptr<AABBCollider> pColliderB)
{
	for (size_t i = 0; i < collisionPairs.size(); i++)
	{
		if (collisionPairs[i]->HasExpired())
			continue;

		if (collisionPairs[i]->DoesCollisionPairExist(pColliderA, pColliderB))
			return;
	}

	if (auto colliderA = pColliderA.lock())
	{
		if (auto colliderB = pColliderB.lock())
		{
			std::shared_ptr<CollisionPair> newPair = std::make_shared<CollisionPair>(colliderA, colliderB);

			if (colliderA->CheckOverlap(colliderB))
			{
				collisionPairs.push_back(newPair);
				newPair->OnEnter();

				std::cout <<"Adding collision pair " << colliderA->object->GetID() << " and " << colliderB->object->GetID() << std::endl;
			}
		}
	}
}

// Check collisions for all stored collision pairs
void CollisionChecker::CheckCollisionPairs()
{
	RemoveExpiredReferences();

	if (collisionPairs.empty())
		return;

	for (size_t i = 0; i < collisionPairs.size(); i++)
	{
		CheckCollision(collisionPairs[i]);
	}
}

void CollisionChecker::CheckCollision(const std::shared_ptr<CollisionPair> pCollisionPair)
{
	std::shared_ptr<AABBCollider> colliderA = pCollisionPair->colliderA.lock();
	std::shared_ptr<AABBCollider> colliderB = pCollisionPair->colliderB.lock();

	if (colliderA->CheckOverlap(colliderB))
	{
		std::shared_ptr<RigidBody> rigidBodyA, rigidBodyB;
		if (colliderA->object->TryGetComponent<RigidBody>(rigidBodyA))
		{
			if (colliderB->object->TryGetComponent<RigidBody>(rigidBodyB))
			{
				// If both objects havea rigid body, resolve rigidbody vs rigidbody collision
				RigidBodyCollision(rigidBodyA, rigidBodyB);
			}
			else
			{
				// If object B does not have a rigidbody, resolve rigidbody vs object
				ObjectCollision(rigidBodyA, colliderB);
			}
		}
		else
		{
			// If object A does not have a rigidbody, resolve object vs rigidbody
			// We can assume that object B has a rigidbody, because the collision would be impossible otherwise
			ObjectCollision(colliderA, colliderB->object->GetComponent<RigidBody>());
		}
	}
	else if (colliderA->HasExitedCollision(colliderB))
	{
		// If the colliders are too far apart, remove their pair from the list
		auto it = std::find(collisionPairs.begin(), collisionPairs.end(), pCollisionPair);
		collisionPairs.erase(it);
	}
}

// Todo: combine both ObjectCollision functions into one

void CollisionChecker::ObjectCollision(const std::shared_ptr<RigidBody> pRigidBody, const std::shared_ptr<AABBCollider> pCollider)
{
	// Calculate how far the rigidbody has penetrated the object
	Vector2 collisionDistance = CalculateCollisionDistance(pRigidBody->collider, pCollider);
	Vector2 normal;

	float shortestCollisionDistance = 0;
	if (collisionDistance.x > collisionDistance.y)
	{
		// Because the objects are sorted left to right, if the rigidbody is moving left the collision is impossible
		if (pRigidBody->velocity.x < 0)
			return;
	
		normal = Vector2(1, 0);
	
		shortestCollisionDistance = collisionDistance.x;
	}
	else
	{
		if (pRigidBody->collider->top < pCollider->top)
		{
			// because the rigidbody is above the collider, if the rigidbody is moving up the collision is impossible
			if (pRigidBody->velocity.y < 0)
				return;
	
			normal = Vector2(0, -1);
		}
		else
		{
			// Vice versa
			if (pRigidBody->velocity.y > 0)
				return;
	
			normal = Vector2(0, 1);
		}
	
		shortestCollisionDistance = collisionDistance.y;
	}

	pRigidBody->HandleCollision(Collision(pCollider->object, normal, shortestCollisionDistance));
}

void CollisionChecker::ObjectCollision(const std::shared_ptr<AABBCollider> pCollider, const std::shared_ptr<RigidBody> pRigidBody)
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

// Todo: find way to incorporate both vertical and horizontal collision into one function

void CollisionChecker::RigidBodyCollision(const std::shared_ptr<RigidBody> pRigidBodyA, const std::shared_ptr<RigidBody> pRigidBodyB)
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

void CollisionChecker::HorizontalRigidBodyCollision(const std::shared_ptr<RigidBody> pRigidBodyA, const std::shared_ptr<RigidBody> pRigidBodyB, float pCollisionDistance)
{
	Vector2 normal, otherNormal;

	// If rigid body B is moving away from A, skip
	if (pRigidBodyB->velocity.x > pRigidBodyA->velocity.x)
		return;

	if (pRigidBodyA->velocity.x > 0)
		normal = Vector2(-1, 0);
	else
		normal = Vector2(1, 0);

	otherNormal = normal * -1;

	// calculate total velocity of the collision
	float totalVelocity = abs(pRigidBodyA->velocity.x) + abs(pRigidBodyB->velocity.x);

	// Calculate the velocity for rigid body A as the percentage of the total velocity
	// Multiply that by the collision distance (penetration depth) to get the amount rigid body A's position needs to be adjusted by
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

	// Same but for rigid body B
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

	const Collision aCollision = Collision(pRigidBodyB->object, normal, velocityAdjustmentA);
	pRigidBodyA->HandleCollision(aCollision);
	const Collision bCollision = Collision(pRigidBodyA->object, otherNormal, velocityAdjustmentB);
	pRigidBodyB->HandleCollision(bCollision);

	CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
}

// Same logic as HorizontalRigidBodyCollision, but applied to the Y axis
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

	topRigidBody->HandleCollision(Collision(bottomRigidBody->object, normal, velocityAdjustmentA));
	bottomRigidBody->HandleCollision(Collision(topRigidBody->object, otherNormal, velocityAdjustmentB));
	CollisionVelocityHandling(pRigidBodyA, pRigidBodyB, normal);
}

// Calculate the adjustments in velocity for both rigidbodies
void CollisionChecker::CollisionVelocityHandling(std::shared_ptr<RigidBody> pRigidBodyA, std::shared_ptr<RigidBody> pRigidBodyB, Vector2 pNormal)
{
	// Crude "bounce" implementation
	if (pRigidBodyA->bounciness > 0 || pRigidBodyB->bounciness > 0)
	{
		pRigidBodyA->HandleBounce(pRigidBodyB);
		pRigidBodyB->HandleBounce(pRigidBodyA);
		return;
	}

	// Get the totalmass of the collision as multiplier
	float totalMass = pRigidBodyA->mass + pRigidBodyB->mass;
	totalMass = 1 / totalMass;

	std::shared_ptr<RigidBody> impactingRigidBody, receivingRigidBody;

	// Determine the rigidbody with the most momentum as the "instigator" of the collision
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

	// Calculate the velocities in case of a Y-axis collision
	if (pNormal.x == 0)
	{
		float maxXVelocity ,minXVelocity;

		if (std::abs(impactingRigidBody->velocity.x)  > std::abs(receivingRigidBody->velocity.x))
		{
			maxXVelocity = impactingRigidBody->velocity.x;
			minXVelocity = receivingRigidBody->velocity.x;
		}
		else
		{
			maxXVelocity = receivingRigidBody->velocity.x;
			minXVelocity = impactingRigidBody->velocity.x;
		}

		// Apply a basic "friction" calculation to the "unimpacted" velocity axis to simulate friction between the two rigid bodies
		float xVelocity = (maxXVelocity * (0.4f / receivingRigidBody->mass) - minXVelocity) * totalMass;

		// Get the difference in velocity between the two rigid bodies and apply the total collision mass to it
		float yVelocity = (impactingRigidBody->velocity.y - receivingRigidBody->velocity.y) * totalMass;

		// Set the velocity correction for "receiving" rigid body
		bImpulse = Vector2(xVelocity, yVelocity);
		// Set the velocity Correction for the instigating rigid body
		aImpulse = Vector2(xVelocity, yVelocity * receivingRigidBody->mass) * -1;
	}

	// Calculate the velocities in case of an X-axis collision
	if (pNormal.y == 0)
	{
		float maxYVelocity ,minYVelocity;

		if (std::abs(impactingRigidBody->velocity.y)  > std::abs(receivingRigidBody->velocity.y))
		{
			maxYVelocity = impactingRigidBody->velocity.y;
			minYVelocity = receivingRigidBody->velocity.y;
		}
		else
		{
			maxYVelocity = receivingRigidBody->velocity.y;
			minYVelocity = impactingRigidBody->velocity.y;
		}

		float xVelocityDifference = (impactingRigidBody->velocity.x - receivingRigidBody->velocity.x) * totalMass;
		float yVelocity = (maxYVelocity * (0.4f / receivingRigidBody->mass) - minYVelocity) * totalMass;
	
		bImpulse = Vector2(xVelocityDifference, yVelocity);
		aImpulse = Vector2(xVelocityDifference * receivingRigidBody->mass, yVelocity) * -1;
	}

	// Apply the velocity corrections as instant forces
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