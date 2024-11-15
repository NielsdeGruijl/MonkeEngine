#include "CollisionChecker.h"

#include "../Objects/Pawn.h"

#include "../Components/SpriteRenderer.h"
#include "../Components/CharacterController.h"

#include "Collision.h"

extern float deltaTime;

void CollisionChecker::AddCollider(std::shared_ptr<AABBCollider> pCollider, bool pIsPawn)
{
	if (pIsPawn)
		pawnColliders.push_back(pCollider);
	else
		objectColliders.push_back(pCollider);
}

void CollisionChecker::AddCharacterController(std::shared_ptr<CharacterController> controller)
{
	characterControllers.push_back(controller);
}

void CollisionChecker::CheckCollisions()
{
	for (std::shared_ptr<AABBCollider> pawnCollider : pawnColliders)
	{
		for (std::shared_ptr<AABBCollider> objectCollider : objectColliders)
		{
			if (pawnCollider->CheckCollision(objectCollider))
				DiscreteCollision(pawnCollider, objectCollider);
		}
	}
}

void CollisionChecker::CheckSweptCollisions()
{
	for (std::shared_ptr<CharacterController> controller : characterControllers)
	{
		for (std::shared_ptr<AABBCollider> objectCollider : objectColliders)
		{
			if (controller->collider->CheckCollision(objectCollider))
				ControllerCollision(controller, objectCollider);
		}
	}
}

void CollisionChecker::DiscreteCollision(std::shared_ptr<AABBCollider> pCollider1, std::shared_ptr<AABBCollider> pCollider2)
{
	Pawn* pawn = static_cast<Pawn*>(pCollider1->GetObject());                  
	Vector2 pawnVelocity = pawn->controller->velocity;

	float xCollisionEntry, yCollisionEntry;
	float xEntryTime, yEntryTime;
	Vector2 normal(0, 0);

	if (pawnVelocity.x != 0)
	{
		if (pawnVelocity.x > 0)
			xCollisionEntry = pCollider2->left - pCollider1->right;
		else
			xCollisionEntry = pCollider2->right - pCollider1->left;

		xEntryTime = xCollisionEntry / pawnVelocity.x;
	}
	else
	{
		xCollisionEntry = -std::numeric_limits<float>::infinity();
		xEntryTime = -std::numeric_limits<float>::infinity();
	}

	if (pawnVelocity.y != 0)
	{
		if (pawnVelocity.y > 0)
			yCollisionEntry = pCollider2->top - pCollider1->bottom;
		else
			yCollisionEntry = pCollider2->bottom - pCollider1->top;

		yEntryTime = yCollisionEntry / pawnVelocity.y;
	}
	else
	{
		yCollisionEntry = -std::numeric_limits<float>::infinity();
		yEntryTime = -std::numeric_limits<float>::infinity();
	}

	if (xEntryTime > yEntryTime)
		normal = Vector2(1, 0);
	else
		normal = Vector2(0, 1);

	float entryTime = std::max<float>(xEntryTime, yEntryTime);

	//std::cout << entryTime << "\n";

	// This if statement ensures that the collision gets resolved on the correct side of the object.
	if (entryTime >= -1)
	{
		//pawn->SetPosition(pawn->position + pawn->controller->velocity * entryTime);

		//std::cout << pCollider1->position.printVector();

		//float remainingTime = 1 + entryTime;
		//Vector2 tVelocity = Vector2(pawnVelocity.x * normal.y, pawnVelocity.y * normal.x);

		//pawn->controller->SetVelocity(tVelocity * remainingTime);

		object = pCollider2->GetObject();
		pawn->controller->HandleCollision(Collision(object, normal, entryTime));
	}
}

void CollisionChecker::ControllerCollision(std::shared_ptr<CharacterController> controller, std::shared_ptr<AABBCollider> pCollider2)
{
	Pawn* pawn = static_cast<Pawn*>(controller->GetObject());
	std::shared_ptr<AABBCollider> pCollider1 = controller->collider;
	Vector2 pawnVelocity = controller->velocity;

	float xCollisionEntry, yCollisionEntry;
	float xEntryTime, yEntryTime;
	Vector2 normal(0, 0);

	if (pawnVelocity.x != 0)
	{
		if (pawnVelocity.x > 0)
			xCollisionEntry = pCollider2->left - pCollider1->right;
		else
			xCollisionEntry = pCollider2->right - pCollider1->left;

		xEntryTime = xCollisionEntry / pawnVelocity.x;
	}
	else
	{
		xCollisionEntry = -std::numeric_limits<float>::infinity();
		xEntryTime = -std::numeric_limits<float>::infinity();
	}

	if (pawnVelocity.y != 0)
	{
		if (pawnVelocity.y > 0)
			yCollisionEntry = pCollider2->top - pCollider1->bottom;
		else
			yCollisionEntry = pCollider2->bottom - pCollider1->top;

		yEntryTime = yCollisionEntry / pawnVelocity.y;
	}
	else
	{
		yCollisionEntry = -std::numeric_limits<float>::infinity();
		yEntryTime = -std::numeric_limits<float>::infinity();
	}

	if (xEntryTime > yEntryTime)
	{
		if (pawnVelocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);
	}
	else
	{
		if(pawnVelocity.y > 0)
			normal = Vector2(0, -1);
		else
			normal = Vector2(0, 1);
	}

	float entryTime = std::max<float>(xEntryTime, yEntryTime);

	// This if statement ensures that the collision gets resolved on the correct side of the object.
	if (entryTime >= -1)
	{
		pawn->SetPosition(pawn->position + pawnVelocity * entryTime);
		//std::cout << pawn->controller->velocity.printVector();

		float remainingTime = 1 + entryTime;
		Vector2 tVelocity = Vector2(pawnVelocity.x * normal.y, pawnVelocity.y * normal.x);

		pawn->controller->SetVelocity(tVelocity * remainingTime);


		object = pCollider2->GetObject();
		//controller->HandleCollision(Collision(object, normal, entryTime));
	}
}

// Clean up DiscreteCollision function and make it pretty :)
// 
// Figure out how the collision detection should be called (automatically for all colliders from collisionchecker or character controllers request collision checks from collisionchecker)
// 
// Implement continuous collision detection
//
// Create a better normal calculation