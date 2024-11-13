#pragma once

#include "../Math/Vector2.h"

class Object;

class Component
{
public:
	Component();
	~Component();

	virtual void Update();

	void SetObject(Object* pObject);
	Object* GetObject() const;

	void SetActive(bool pIsActive);
	bool IsActive();

protected:
	Object* object;
	bool isActive;
};