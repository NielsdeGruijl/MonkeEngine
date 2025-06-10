#include "LeftObject.h"
#pragma once

LeftObject::LeftObject(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	moveSpeed = 0;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->bounciness = 1;

	AddComponent<SpriteRenderer>(this, "BlueSlime.png");
}

void LeftObject::Update()
{
	GameObject::Update();
}

void LeftObject::FixedUpdate()
{
	rigidBody->AddForce(Vector2(moveSpeed * moveDirection, 0), RigidBody::velocityChange);
	GameObject::FixedUpdate();
}

void LeftObject::OnCollisionEnter(GameObject* object)
{
	GameObject::OnCollisionEnter(object);
	moveDirection *= -1;
}
