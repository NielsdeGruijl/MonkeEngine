#include "LeftObject.h"
#pragma once

LeftObject::LeftObject(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;

	AddComponent<SpriteRenderer>(this, "BlueSlime.png");
}

void LeftObject::Update()
{
	GameObject::Update();
	rigidBody->AddForce(Vector2(3 * moveDirection, 0));
}
