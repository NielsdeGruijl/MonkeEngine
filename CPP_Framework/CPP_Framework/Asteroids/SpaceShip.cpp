#pragma once
#include "SpaceShip.h"

SpaceShip::SpaceShip(std::string pId, std::string pFileName, int pPixelsPerUnit)
	: GameObject(pId, pFileName, pPixelsPerUnit)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
}

SpaceShip::~SpaceShip()
{
}
