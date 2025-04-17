#pragma once

#include "../../Framework/Objects/GameObject.h"
#include "../../Framework/Components/RigidBody.h"
#include "../../Framework/Components/SpriteRenderer.h"

class PowerupObject : public GameObject
{
public:
	PowerupObject(Scene* pScene, std::string pObjectId);
	~PowerupObject();

	std::shared_ptr<RigidBody> rigidBody;

	float bulletSizeMultiplier;
};