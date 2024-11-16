#include "Component.h"

#include "../Objects/Object.h"

Component::Component()
{
	object = nullptr;
	isActive = true;
}

Component::~Component()
{
}

void Component::Update()
{
}

void Component::SetActive(bool pIsActive)
{
	isActive = pIsActive;
}

void Component::SetObject(Object* pObject)
{
	object = pObject;
}

Object* Component::GetObject() const
{
	return object;
}

void Component::OnLoad()
{
}

bool Component::IsActive()
{
	return isActive;
}
