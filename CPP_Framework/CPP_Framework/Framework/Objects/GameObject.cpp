#include "GameObject.h"

GameObject::GameObject(std::string pID, std::string pFileName, int pPixelsPerUnit) 
	: Object(pID), sprite(pFileName, pPixelsPerUnit)
{
	SetOrigin(Vector2(0.5f, 0.5f));
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	Object::Update();
}

void GameObject::Render(sf::RenderWindow* pRenderWindow)
{
	pRenderWindow->draw(sprite.sprite);
}

void GameObject::SetPosition(const Vector2 pPosition)
{
	Object::SetPosition(pPosition);
	sprite.SetPosition(pPosition);
}

void GameObject::SetScale(const Vector2 pScale)
{
	Object::SetScale(pScale);
	sprite.SetScale(pScale);
}

void GameObject::SetScale(const float pScale)
{
	SetScale(Vector2(pScale, pScale));
}

void GameObject::SetOrigin(const Vector2 pOrigin)
{
	Object::SetOrigin(pOrigin);
	sprite.SetOrigin(pOrigin);
}