#include "Component.h"

#include "../Objects/GameObject.h"

Component::Component(GameObject* pObject)
{
	object = pObject;
	isActive = true;
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}

void Component::SetActive(bool pIsActive)
{
	isActive = pIsActive;
}

void Component::OnLoad()
{
}

bool Component::IsActive()
{
	return isActive;
}