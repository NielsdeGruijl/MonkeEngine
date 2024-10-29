#include "Player.h"
#include "../Framework/Math/Time.h"

extern Time _time;

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: Pawn(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);
}

Player::~Player() 
{
}

void Player::Update()
{
	velocity = Vector2((float)input.GetHorizontalAxis(), (float)input.GetVerticalAxis());

	if (velocity.GetLength() > 0)
		controller.Move(velocity.normalized * moveSpeed * _time.deltaTime);
	
	if (input.GetKeyDown("test"))
	{
		std::cout << "player GetKeyDown \n";
	}

	if (input.GetKeyUp("test"))
	{
		std::cout << "Test getkey up " << "\n";
	}

	defaultInputActionMap.UpdateKeyStatus();
}

void Player::SetActionMap(InputActionMap* playerInputActionMap)
{
	input.SetInputActionMap(playerInputActionMap);
}