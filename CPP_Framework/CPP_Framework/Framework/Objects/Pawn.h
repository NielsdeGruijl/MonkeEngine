#pragma once

#include "GameObject.h"
#include "../Components/RigidBody.h"
#include "../Collisions/AABBCollider.h"

class Pawn : public GameObject
{
public:
	Pawn(std::string objectId, std::string fileName, int pixelsPerUnit = 100);
	~Pawn();

	void Update() override;

	std::shared_ptr<RigidBody> rigidBody;
};