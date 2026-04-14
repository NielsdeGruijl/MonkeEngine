#include "LeftObject.h"
//#pragma once

LeftObject::LeftObject(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	moveSpeed = 0.5f;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->bounciness = 1;

	AddComponent<SpriteRenderer>(this, "BlueSlime.png");
}

void LeftObject::OnLoad()
{
	GameObject::OnLoad();

}

void LeftObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void LeftObject::FixedUpdate(float fixedDeltaTime)
{
	rigidBody->AddForce(Vector2(moveSpeed * moveDirection, 0) * fixedDeltaTime, RigidBody::velocityChange);
	GameObject::FixedUpdate(fixedDeltaTime);
}

void LeftObject::OnCollisionEnter(GameObject* object)
{
	GameObject::OnCollisionEnter(object);

	moveDirection *= -1;
}
