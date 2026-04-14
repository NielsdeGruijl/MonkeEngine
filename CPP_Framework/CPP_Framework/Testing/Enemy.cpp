#include "Enemy.h"

Enemy::Enemy(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->bounciness = 0;

	moveSpeed = -2;

	sprite = AddComponent<SpriteRenderer>(this, "BlueSlime.png");
	sprite->SetColor(sf::Color::Red);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	Vector2 tempVelocity = Vector2(moveSpeed, 0) * deltaTime;
	rigidBody->AddForce(tempVelocity);
}
