#pragma once

#include "GameObject.h"
#include "../Components/CharacterController.h"
#include "../Collisions/AABBCollider.h"

class Pawn : public GameObject
{
public:
	Pawn(std::string objectId, std::string fileName, int pixelsPerUnit = 100);
	~Pawn();

	void Update() override;

protected:
	//CharacterController controller;
	std::shared_ptr<CharacterController> controller;
};