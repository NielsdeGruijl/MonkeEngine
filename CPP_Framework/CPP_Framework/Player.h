#pragma once

#include "Pawn.h"

class Player : public Pawn
{
public:
	Player(std::string objectId, std::string fileName, int pixelsPerUnit);
	~Player();

	void Update() override;

	void SetActionMap(InputActionMap* map);

private:
	InputHandler input;
	Vector2 velocity;

	float moveSpeed = 200;
};
