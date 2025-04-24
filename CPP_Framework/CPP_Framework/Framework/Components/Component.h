#pragma once

#include "../Math/Vector2.h"

class GameObject;

class Component
{
public:
	GameObject* object;

public:
	Component(GameObject* pObject);
	~Component();

	virtual void Update();

	virtual void OnLoad();

	void SetActive(bool pIsActive);
	bool IsActive();

protected:
	bool isActive;
};