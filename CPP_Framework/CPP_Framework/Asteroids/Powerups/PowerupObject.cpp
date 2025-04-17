#pragma once

#include "PowerupObject.h"
#include "BigBulletPowerup.h"

PowerupObject::PowerupObject(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	bulletSizeMultiplier = 2;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 3;

	rigidBody->collider->isTrigger = true;

	AddComponent<BigBulletPowerup>(this, "PurpleJunimo.png");
}

PowerupObject::~PowerupObject()
{
}
