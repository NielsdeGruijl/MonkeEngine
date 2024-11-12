#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(std::string pID, std::string pFileName, int pPixelsPerUnit)
	: Pawn(pID, pFileName, pPixelsPerUnit)
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update()
{
	Pawn::Update();

	controller->SetVelocity(Vector2(250, 0));
}