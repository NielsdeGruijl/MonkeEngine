#include "Player.h"
#include "../Framework/Math/Time.h"

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: Pawn(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);

	moveSpeed = 6;
	dashSpeed = 10;

	controller->drag = 1;
	controller->gravity = 0;
}

Player::~Player() 
{
}

void Player::Update()
{
	Pawn::Update();
	velocity = Vector2((float)input.GetHorizontalAxis(), (float)input.GetVerticalAxis());

	if (velocity.GetLength() > 0)
		controller->AddVelocity(velocity.normalized * moveSpeed);
	
	if (input.GetKeyDown("dash"))
	{
		controller->AddVelocity(Vector2(1,0) * dashSpeed, CharacterController::instant);
	}

	if (input.GetKeyDown("test"))
		SetScale(1);
		

	defaultInputActionMap.UpdateKeyStatus();
}

void Player::SetActionMap(InputActionMap* playerInputActionMap)
{
	input.SetInputActionMap(playerInputActionMap);
}