#include "Asteroid.h"
#include "../Framework/Core/Scene.h"

Asteroid::Asteroid(Scene* pScene, std::string pId, std::string pFileName, int pPixelsPerUnit)
	: GameObject(pScene, pId, pFileName,pPixelsPerUnit)
{
	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 1;
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

void Asteroid::OnCollisionEnter()
{
	Object::OnCollisionEnter();
}

void Asteroid::OnParamCollisionEnter(Object* object)
{
	Object::OnParamCollisionEnter(object);
	Destroy();
}