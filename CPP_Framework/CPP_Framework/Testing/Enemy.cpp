#include "Enemy.h"

Enemy::Enemy(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->bounciness = 0;
	rigidBody->mass = 2.5f;

	moveSpeed = 0;

	sprite = AddComponent<SpriteRenderer>(this, "BlueSlime.png");
	sprite->SetColor(sf::Color::Red);

	// rigidBody->AddForce(Vector2(1, 0), RigidBody::instant);
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

void Enemy::OnCollisionEnter(std::weak_ptr<AABBCollider> pOtherCollider)
{
	GameObject::OnCollisionEnter(pOtherCollider);
}

void Enemy::OnCollisionExit(std::weak_ptr<AABBCollider> pOtherCollider)
{
	GameObject::OnCollisionExit(pOtherCollider);
}
