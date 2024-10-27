#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player(std::string objectId, std::string fileName, int pixelsPerUnit);
	~Player();

	void Update() override;

private:
	Vector2 velocity;

	float moveSpeed = 200;
};
