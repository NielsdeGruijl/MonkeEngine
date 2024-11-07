#include "Player.h"
#include "../Framework/Math/Time.h"

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: Pawn(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);

	moveSpeed = 2;
	dashSpeed = 3;

	controller.drag = 1;
	controller.useGravity = false;

	//std::cout << sprite.sprite.getGlobalBounds().width << ", " << sprite.sprite.getGlobalBounds().height << "\n";
}

Player::~Player() 
{
}

void Player::Update()
{
	Pawn::Update();
	velocity = Vector2((float)input.GetHorizontalAxis(), (float)input.GetVerticalAxis());

	if (velocity.GetLength() > 0)
		controller.AddVelocity(velocity.normalized * moveSpeed);
	
	if (input.GetKeyDown("dash"))
	{
		SetScale(5);
	}

	if (input.GetKeyDown("test"))
		SetScale(1);
		//controller.AddVelocity(velocity.normalized * dashSpeed, CharacterController::instant);

	defaultInputActionMap.UpdateKeyStatus();
}

void Player::SetActionMap(InputActionMap* playerInputActionMap)
{
	input.SetInputActionMap(playerInputActionMap);
}