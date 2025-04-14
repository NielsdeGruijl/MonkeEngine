#include "Bullet.h"
#include "../Framework/Core/Scene.h"


Bullet::Bullet(Scene* pScene, std::string pObjectId, std::string pSpriteFileName, int pPixelsPerUnit)
	: GameObject(pScene, pObjectId, pSpriteFileName, pPixelsPerUnit)
{
	moveSpeed = 10;

	SetScale(0.25f);

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->drag = 0;
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
		Destroy();
	}
}

void Bullet::Destroy()
{
	scene->RemoveObject(this);

	delete this;
}

void Bullet::OnCollisionEnter()
{
	Object::OnCollisionEnter();

	Destroy();
}
