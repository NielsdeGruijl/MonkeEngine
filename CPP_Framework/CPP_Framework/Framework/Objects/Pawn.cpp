#include "Pawn.h"

Pawn::Pawn(std::string pID, std::string pFileName, int pPixelsPerUnit) 
	: GameObject(pID, pFileName, pPixelsPerUnit)
{
	rigidBody = AddComponent<RigidBody>(1, 1, 1);
}

Pawn::~Pawn()
{
}

void Pawn::Update()
{
	GameObject::Update();
}