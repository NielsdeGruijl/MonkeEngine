#pragma once

#include <iostream>
#include "AABBCollider.h"
#include "../Components/CharacterController.h"

class CollisionChecker
{
public:
	void AddCollider(std::shared_ptr<AABBCollider> pCollider, bool pIsPawn = false);
	void AddCharacterController(std::shared_ptr<CharacterController> controller);
	void CheckCollisions();
	void CheckSweptCollisions();
	void DiscreteCollision(std::shared_ptr<AABBCollider> pCollider1, std::shared_ptr<AABBCollider> pCollider2);
	void ControllerCollision(std::shared_ptr<CharacterController> controller, std::shared_ptr<AABBCollider> pCollider2);

private:
	std::vector<std::shared_ptr<CharacterController>> characterControllers;
	std::vector<std::shared_ptr<AABBCollider>> pawnColliders;
	std::vector<std::shared_ptr<AABBCollider>> objectColliders;

	Object* object;
};