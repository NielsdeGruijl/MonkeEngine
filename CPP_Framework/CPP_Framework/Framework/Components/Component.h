#pragma once

#include "../Math/Vector2.h"

class GameObject;

class Component
{
public:
	GameObject* object;

public:
	explicit Component(GameObject* pObject);
	virtual ~Component();

	virtual void Update(float deltaTime);

	virtual void OnLoad();

	void SetActive(bool pIsActive);
	bool IsActive();

protected:
	bool isActive;
};