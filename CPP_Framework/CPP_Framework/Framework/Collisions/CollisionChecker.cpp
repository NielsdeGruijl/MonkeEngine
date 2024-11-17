#include "CollisionChecker.h"

#include "../Objects/Pawn.h"

#include "../Components/SpriteRenderer.h"
#include "../Components/CharacterController.h"

#include "../Math/Timer.h";

#include "Collision.h"

extern float deltaTime;

void CollisionChecker::AddCollider(std::shared_ptr<AABBCollider> pCollider)
{
	objectColliders.push_back(pCollider);
}

void CollisionChecker::AddCharacterController(std::shared_ptr<CharacterController> controller)
{
	characterControllers.push_back(controller);
}

void CollisionChecker::CheckCollisions()
{
	Timer timer;

	for (size_t i = 0; i < characterControllers.size(); i++)
	{
		for (size_t j = 0; j < objectColliders.size(); j++)
		{
			if (characterControllers[i]->collider == objectColliders[j])
				continue;

			if (characterControllers[i]->collider->CheckCollision(objectColliders[j]))
				PawnToObjectCollision(characterControllers[i], objectColliders[j]);
		}
	}
}

void CollisionChecker::PawnToObjectCollision(std::shared_ptr<CharacterController> pController, std::shared_ptr<AABBCollider> pCollider)
{
	Vector2 tEntryTime = CalculateEntryTime(pController, pCollider);
	Vector2 normal(0, 0);

	if (tEntryTime.x > tEntryTime.y)
	{
		if (pController->velocity.x > 0)
			normal = Vector2(-1, 0);
		else
			normal = Vector2(1, 0);
	}
	else
	{
		if(pController->velocity.y > 0)
			normal = Vector2(0, -1);
		else
			normal = Vector2(0, 1);
	}

	float entryTime = std::max<float>(tEntryTime.x, tEntryTime.y);

	if (entryTime >= -1)
	{
		object = pCollider->GetObject();
		pController->HandleCollision(Collision(object, normal, entryTime));
	}
}

Vector2 CollisionChecker::CalculateEntryTime(std::shared_ptr<CharacterController> pController, std::shared_ptr<AABBCollider> pObjectCollider)
{
	std::shared_ptr<AABBCollider> controllerCollider = pController->collider;
	Vector2 pawnVelocity = pController->velocity;
	float xCollisionEntry, yCollisionEntry;
	float xEntryTime, yEntryTime;

	if (pawnVelocity.x != 0)
	{
		if (pawnVelocity.x > 0)
			xCollisionEntry = pObjectCollider->left - controllerCollider->right;
		else
			xCollisionEntry = pObjectCollider->right - controllerCollider->left;

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
			yCollisionEntry = pObjectCollider->top - controllerCollider->bottom;
		else
			yCollisionEntry = pObjectCollider->bottom - controllerCollider->top;

		yEntryTime = yCollisionEntry / pawnVelocity.y;
	}
	else
	{
		yCollisionEntry = -std::numeric_limits<float>::infinity();
		yEntryTime = -std::numeric_limits<float>::infinity();
	}

	return Vector2(xEntryTime, yEntryTime);
}

// Clean up DiscreteCollision function and make it pretty :)
// 
// Implement continuous collision detection
//
// Create a better normal calculation