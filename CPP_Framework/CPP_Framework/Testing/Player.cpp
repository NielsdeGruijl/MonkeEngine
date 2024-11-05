#include "Player.h"
#include "../Framework/Math/Time.h"

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: Pawn(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);

	moveSpeed = 2;
	dashSpeed = 1;

	controller.drag = 2;
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
		std::cout << "DASH \n";
		controller.AddVelocity(velocity.normalized * dashSpeed, CharacterController::instant);
		std::cout << position.printVector() << "\n";
	}

	defaultInputActionMap.UpdateKeyStatus();
}

void Player::SetActionMap(InputActionMap* playerInputActionMap)
{
	input.SetInputActionMap(playerInputActionMap);
}