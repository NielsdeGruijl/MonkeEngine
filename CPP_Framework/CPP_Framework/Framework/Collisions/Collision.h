#pragma once

#include <iostream>
#include "../Math//Vector2.h"
#include "../Objects/Object.h"

struct Collision
{
	Collision(Object* pOther, Vector2 pNormal, float pEntryTime)
	{
		other = pOther;
		normal = pNormal;
		entryTime = pEntryTime;
		remainingTime = 1 + entryTime;
	}

	~Collision()
	{
	}

	Object* other;
	Vector2 normal;

	float entryTime;
	float remainingTime;
};