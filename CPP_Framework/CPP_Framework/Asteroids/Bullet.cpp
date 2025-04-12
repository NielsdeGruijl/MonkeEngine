#include "Bullet.h"
#include "../Framework/Core/Scene.h"


Bullet::Bullet(Scene* pScene, std::string pObjectId, std::string pSpriteFileName, int pPixelsPerUnit)
	: GameObject(pScene, pObjectId, pSpriteFileName, pPixelsPerUnit)
{
	moveSpeed = 10;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->drag = 0;

	SetScale(0.25f);
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	GameObject::Start();
	lifeTime.restart();

	rigidBody->AddForce(Vector2(0, -moveSpeed), RigidBody::instant);
}

void Bullet::Update()
{
	GameObject::Update();

	if (lifeTime.getElapsedTime().asSeconds() > 1)
	{
		scene->RemoveObject(this);

		delete this;
	}
}
