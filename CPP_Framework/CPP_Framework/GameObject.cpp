#include "GameObject.h"

GameObject::GameObject(std::string ID, std::string fileName, int pixelsPerUnit) 
	: Object(ID), sprite(fileName, pixelsPerUnit)
{
	sprite.SetPosition(position);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

}

void GameObject::Render(sf::RenderWindow* window)
{
	window->draw(sprite.sprite);
}

void GameObject::SetPosition(const Vector2 position)
{
	Object::SetPosition(position);
	sprite.SetPosition(position);
}

void GameObject::SetScale(const Vector2 size)
{
	sprite.SetScale(size);
}