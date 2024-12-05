#pragma once

#include "../Framework/Objects/Pawn.h"
#include "../Framework/Input/InputActionMap.h"
#include "../Framework/Input/InputHandler.h"

class Player : public Pawn
{
public:
	Player(std::string pObjectId, std::string pFileName, int pPixelsPerUnit);
	~Player();

	void Update() override;

	void SetActionMap(InputActionMap* pMap);

protected:
	void OnCollisionEnter() override;
	void OnCollisionStay() override;
	void OnCollisionExit() override;

private:
	InputActionMap defaultInputActionMap;
	InputHandler input;

	Vector2 inputMoveDirection;

	float moveSpeed;
	float dashSpeed;

	bool balls = false;
};
