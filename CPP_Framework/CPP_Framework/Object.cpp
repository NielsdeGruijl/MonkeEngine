#include "Object.h"

Object::Object(std::string ID) : objectId(ID)
{
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Render(sf::RenderWindow* renderWindow)
{
}

void Object::SetScene(Scene* scene)
{
	this->scene = scene;
}

void Object::SetPosition(Vector2 postion)
{
	this->position = postion;
}

std::string Object::GetID() const
{
	return this->objectId;
}