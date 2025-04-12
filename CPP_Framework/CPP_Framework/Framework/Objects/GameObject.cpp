#include "GameObject.h"

GameObject::GameObject(Scene* pScene, std::string pID, std::string pFileName, int pPixelsPerUnit) 
	: Object(pScene, pID)
{
	AddComponent<SpriteRenderer>(this, pFileName, pPixelsPerUnit);

	spriteRenderer = GetComponent<SpriteRenderer>();

	SetOrigin(Vector2(0.5f, 0.5f));
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
	Object::Start();
}

void GameObject::Update()
{
	Object::Update();
}

void GameObject::Render(sf::RenderWindow* pRenderWindow)
{
	pRenderWindow->draw(spriteRenderer->sprite);
}

void GameObject::SetPosition(const Vector2 pPosition)
{
	Object::SetPosition(pPosition);
}

void GameObject::SetScale(const Vector2 pScale)
{
	Object::SetScale(pScale);
	spriteRenderer->SetScale(pScale);
}

void GameObject::SetScale(const float pScale)
{
	SetScale(Vector2(pScale, pScale));
}

void GameObject::SetOrigin(const Vector2 pOrigin)
{
	Object::SetOrigin(pOrigin);
	spriteRenderer->SetOrigin(pOrigin);
}