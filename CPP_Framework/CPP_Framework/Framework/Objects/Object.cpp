#include "Object.h"

extern const int unitSize;

Object::Object(std::string ID) 
	: objectId(ID)
{
	size = Vector2(unitSize, unitSize);
}

Object::~Object()
{
}

std::string Object::GetID() const
{
	return objectId;
}

void Object::SetScale(const Vector2 pScale)
{
	size = Vector2(unitSize * pScale.x, unitSize * pScale.y);
}

void Object::SetPosition(const Vector2 pPosition)
{
	position = pPosition;
}

void Object::SetOrigin(const Vector2 pOrigin)
{
	origin = size * pOrigin;
}