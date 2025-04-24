#pragma once

#include "../../Framework/Objects/GameObject.h"

#include "BasePowerup.h"

class BigBulletPowerup : public BasePowerup
{
public:
	BigBulletPowerup(GameObject* pObject, std::string pFileName)
		: BasePowerup(pObject, pFileName)
	{
		bulletSizeMultiplier = 3;
	}
};