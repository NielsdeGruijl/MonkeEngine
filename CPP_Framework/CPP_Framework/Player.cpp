#include "Player.h"
#include "Time.h"

extern Time _time;

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit) 
	: Pawn(objectId, fileName, pixelsPerUnit)
{
}

Player::~Player() 
{
}

void Player::Update()
{
	velocity = Vector2(input.GetHorizontalAxis(), input.GetVerticalAxis());

	if (velocity.GetLength() > 0)
		controller.Move(velocity.normalized * moveSpeed * _time.deltaTime);
	
	//if (input.GetKeyDown("test"))
	//{
	//	std::cout << "player GetKeyDown \n";
	//}

	if (input.GetKeyUp("test"))
	{
		std::cout << "Test getkey up" << "\n";
	}
}

void Player::SetActionMap(InputActionMap* map)
{
	input.inputActions = map;
}