#pragma once

#include "../Math/Vector2.h"

class Object;

class Component
{
public:
	Object* object;

public:
	Component(Object* pObject);
	~Component();

	virtual void Update();

	virtual void OnLoad();

	void SetActive(bool pIsActive);
	bool IsActive();

protected:
	bool isActive;
};