#include "Object.h"

Object::Object(std::string ID) 
	: objectId(ID)
{
}

Object::~Object()
{
}

void Object::SetPosition(Vector2 postion)
{
	this->position = postion;
}

std::string Object::GetID() const
{
	return this->objectId;
}