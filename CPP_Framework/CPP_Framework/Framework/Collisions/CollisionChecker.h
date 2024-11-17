#pragma once

#include <iostream>
#include "AABBCollider.h"
#include "../Components/CharacterController.h"

class CollisionChecker
{
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider);
	void AddCharacterController(std::shared_ptr<CharacterController> controller);

	void CheckCollisions();
	void PawnToObjectCollision(std::shared_ptr<CharacterController> pController, std::shared_ptr<AABBCollider> pCollider);

	Vector2 CalculateEntryTime(std::shared_ptr<CharacterController> pController, std::shared_ptr<AABBCollider> pCollider);

private:
	std::vector<std::shared_ptr<CharacterController>> characterControllers;
	std::vector<std::shared_ptr<AABBCollider>> objectColliders;

	Object* object;
	Object* object1;
};