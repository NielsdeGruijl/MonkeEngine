#pragma once

class AABBCollider
{

public:
	AABBCollider();
	~AABBCollider();

	void CheckCollision(AABBCollider otherCollider);
};