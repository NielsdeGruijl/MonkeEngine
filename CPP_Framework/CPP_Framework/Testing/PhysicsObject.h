#pragma once

#include "../Framework/Objects/Pawn.h"
#include "../Framework/Collisions/AABBCollider.h"

class PhysicsObject : public Pawn
{
public:
	PhysicsObject(std::string pID, std::string pFileName, int pPixelsPerUnit = 100);
	~PhysicsObject();

	void Update() override;
};