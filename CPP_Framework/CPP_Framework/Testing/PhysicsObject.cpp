#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(std::string pID, std::string pFileName, int pPixelsPerUnit)
	: Pawn(pID, pFileName, pPixelsPerUnit)
{
	//controller->SetVelocity(Vector2(250, 0));
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update()
{
	Pawn::Update();

	
}