#include "Pawn.h"
#include "Time.h"

extern Time _time;

Pawn::Pawn(std::string ID, std::string fileName, int pixelsPerUnit) 
	: GameObject(ID, fileName, pixelsPerUnit  ), controller(this)
{
	pawnPosition = position;
}

Pawn::~Pawn()
{
}

void Pawn::Update()
{
}