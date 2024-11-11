#include "Pawn.h"
#include "../Math/Time.h"

Pawn::Pawn(std::string pID, std::string pFileName, int pPixelsPerUnit) 
	: GameObject(pID, pFileName, pPixelsPerUnit), controller(this)
{
}

Pawn::~Pawn()
{
}

void Pawn::Update()
{
	GameObject::Update();
	controller.Update();
}