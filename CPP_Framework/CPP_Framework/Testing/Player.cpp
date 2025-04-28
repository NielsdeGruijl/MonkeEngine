#include "Player.h"
#include "../Framework/Components/SpriteRenderer.h"

Player::Player(Scene* pScene, std::string objectId)
	: GameObject(pScene, objectId), input()
{
	SetActionMap(&defaultInputActionMap);

	rigidBody = AddComponent<RigidBody>(this);

	AddComponent<SpriteRenderer>(this, "BlueSlime.png");

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

void Player::OnCollisionEnter(GameObject* pObject)
{
	std::cout << "enter\n";
}

void Player::OnCollisionStay(GameObject* pObject)
{
	std::cout << "stay\n";
}

void Player::OnCollisionExit(GameObject* pObject)
{
	std::cout << "exit\n";
}