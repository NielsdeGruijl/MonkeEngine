#include "Obstacle.h"

Obstacle::Obstacle(std::string pID, std::string pFileName, int pPixelsPerUnit)
	: GameObject(pID, pFileName, pPixelsPerUnit)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	GameObject::Update();
}
