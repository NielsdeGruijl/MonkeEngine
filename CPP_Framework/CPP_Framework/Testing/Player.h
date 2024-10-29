#pragma once

#include "../Framework/Objects/Pawn.h"
#include "../Framework/Input/InputActionMap.h"
#include "../Framework/Input/InputHandler.h"

class Player : public Pawn
{
public:
	Player(std::string objectId, std::string fileName, int pixelsPerUnit);
	~Player();

	void Update() override;

	void SetActionMap(InputActionMap* map);

private:
	InputActionMap defaultInputActionMap;
	InputHandler input;
	Vector2 velocity;

	float moveSpeed = 200;
};
