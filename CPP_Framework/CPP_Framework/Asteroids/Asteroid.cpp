#include "Asteroid.h"
#include "../Framework/Core/Scene.h"

Asteroid::Asteroid(Scene* pScene, std::string pId)
	: GameObject(pScene, pId)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 1;

	SetScale(1);

	sprite = AddComponent<SpriteRenderer>(this, "Cat.jpg", 236);
}

Asteroid::~Asteroid()
{
}

void Asteroid::Start()
{
	GameObject::Start();
}

void Asteroid::Update()
{
	GameObject::Update();
}

void Asteroid::OnCollisionEnter(GameObject* pObject)
{
	GameObject::OnCollisionEnter(pObject);
	Destroy();
}