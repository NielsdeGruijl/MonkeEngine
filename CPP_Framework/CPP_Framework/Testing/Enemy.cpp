#pragma once
#include "Enemy.h"

Enemy::Enemy(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;

	sprite = AddComponent<SpriteRenderer>(this, "BlueSlime.png");
	sprite->SetColor(sf::Color::Red);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	GameObject::Update();
	rigidBody->AddForce(Vector2(-1, 0));
}
