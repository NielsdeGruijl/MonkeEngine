#pragma once

#include "../../Framework/Components/SpriteRenderer.h"
#include "../../Framework/objects/GameObject.h"

class BasePowerup : public Component
{
public:
	BasePowerup(GameObject* pObject, std::string pFileName)
		: Component(pObject)
	{
		pObject->AddComponent<SpriteRenderer>(pObject, pFileName);
		bulletSizeMultiplier = 0;
	}

	float bulletSizeMultiplier;
};