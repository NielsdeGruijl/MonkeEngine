#include "Pawn.h"
#include "../Math/Time.h"

Pawn::Pawn(std::string pID, std::string pFileName, int pPixelsPerUnit) 
	: GameObject(pID, pFileName, pPixelsPerUnit)
{
	AddComponent<CharacterController>(1, 1, 1);

	controller = GetComponent<CharacterController>();
}

Pawn::~Pawn()
{
}

void Pawn::Update()
{
	GameObject::Update();
}