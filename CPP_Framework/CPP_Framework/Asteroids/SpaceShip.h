#pragma once

#include "../Framework/Input/InputActionMap.h"
#include "../Framework/Input/InputHandler.h"

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"

class SpaceShip : public GameObject
{
public:
	SpaceShip(std::string pId, std::string pFileName, int pPixelsPerUnit);
	~SpaceShip();

	std::shared_ptr<RigidBody> rigidBody;
};