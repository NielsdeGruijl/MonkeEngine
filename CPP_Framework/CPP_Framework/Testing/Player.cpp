#include "Player.h"

Player::Player(std::string objectId, std::string fileName, int pixelsPerUnit)
	: GameObject(objectId, fileName, pixelsPerUnit), input()
{
	SetActionMap(&defaultInputActionMap);

	rigidBody = AddComponent<RigidBody>(this);

	moveSpeed = 6;
	dashSpeed = 10;

	rigidBody->drag = 1;
	rigidBody->mass = 1;
	rigidBody->gravity = 0;
}

Player::~Player() 
{
}

void Player::OnLoad()
{
	GameObject::OnLoad();
}

void Player::Start()
{
	GameObject::Start();
}

void Player::Update()
{
	std::shared_ptr<AABBCollider> col;

	GameObject::Update();

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