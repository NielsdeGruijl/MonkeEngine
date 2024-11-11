#pragma once

#include "../Math/Vector2.h"

class Object;

class Component
{
public:
	Vector2 position;

public:
	Component(bool pIsActive = true);
	~Component();

	virtual void Update();

	void SetActive(bool pIsActive);
	void SetObject(Object* pObject);
	
	bool IsActive();

protected:
	Object* object;
	bool isActive;
};