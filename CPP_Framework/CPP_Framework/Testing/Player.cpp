#include "Player.h"

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: Pawn(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);

	moveSpeed = 6;
	dashSpeed = 10;
}

Player::~Player() 
{
}

void Player::Update()
{
	Pawn::Update();

	inputMoveDirection = Vector2((float)input.GetHorizontalAxis(), (float)input.GetVerticalAxis());

	if (inputMoveDirection.GetLength() > 0)
		rigidBody->AddForce(inputMoveDirection.normalized * moveSpeed);
	
	if (input.GetKeyDown("dash"))
	{
		rigidBody->AddForce(Vector2(1,0) * dashSpeed, RigidBody::instant);
	}

	if (input.GetKeyDown("test"))
		SetScale(1);

	defaultInputActionMap.UpdateKeyStatus();
}

void Player::SetActionMap(InputActionMap* playerInputActionMap)
{
	input.SetInputActionMap(playerInputActionMap);
}

void Player::OnCollisionEnter()
{
	std::cout << "enter\n";
}

void Player::OnCollisionStay()
{
	std::cout << "stay\n";
}

void Player::OnCollisionExit()
{
	std::cout << "exit\n";
}