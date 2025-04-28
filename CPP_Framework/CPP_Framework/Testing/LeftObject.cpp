#include "LeftObject.h"
#pragma once

LeftObject::LeftObject(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	moveSpeed = 3;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;

	AddComponent<SpriteRenderer>(this, "BlueSlime.png");
}

void LeftObject::Update()
{
	GameObject::Update();
	rigidBody->AddForce(Vector2(moveSpeed * moveDirection, 0));
}

void LeftObject::OnCollisionEnter(GameObject* object)
{
	GameObject::OnCollisionEnter(object);
	moveDirection *= -1;

	std::cout << "balls\n";
}
