#include "Bullet.h"
#include "../Framework/Core/Scene.h"


Bullet::Bullet(Scene* pScene, std::string pObjectId)
	: GameObject(pScene, pObjectId)
{
	moveSpeed = 10;


	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->drag = 0;

	sprite = AddComponent<SpriteRenderer>(this, "Cat.jpg", 236);

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
		Destroy();
	}
}

void Bullet::OnCollisionEnter()
{
	GameObject::OnCollisionEnter();

}

void Bullet::OnParamCollisionEnter(GameObject* object)
{
	GameObject::OnParamCollisionEnter(object);
	
	if(object)
		std::cout << object->GetID();

	Destroy();
}