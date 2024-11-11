#include "Component.h"

#include "../Objects/Object.h"

Component::Component(bool pIsActive)
{
	object = nullptr;
	isActive = pIsActive;
}

Component::~Component()
{
}

void Component::Update()
{
	position = object->position;
}

void Component::SetActive(bool pIsActive)
{
	isActive = pIsActive;
}

void Component::SetObject(Object* pObject)
{
	object = pObject;
}

bool Component::IsActive()
{
	return isActive;
}
