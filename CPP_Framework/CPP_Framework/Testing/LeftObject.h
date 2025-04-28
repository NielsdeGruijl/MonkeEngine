#pragma once

#include "../FrameWork/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Components/SpriteRenderer.h"

class LeftObject : public GameObject
{
public:
	LeftObject(Scene* pScene, std::string pObjectId);

	void Update() override;

public:
	float moveDirection;

private:
	std::shared_ptr<RigidBody> rigidBody;
};