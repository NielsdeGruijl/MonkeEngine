#pragma once

#include "../Framework/Core/Scene.h"

#include "SpaceShip.h"
#include "Bullet.h"


SpaceShip::SpaceShip(Scene* pScene, std::string pId)
	: GameObject(pScene, pId), input()
{
	moveSpeed = 5;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;

	sprite = AddComponent<SpriteRenderer>(this, "Spaceship.png", 160);

	inputActionMap.ClearMap();
	inputActionMap.AddKey("left", InputAction(sf::Keyboard::A));
	inputActionMap.AddKey("right", InputAction(sf::Keyboard::D));
	inputActionMap.AddKey("fire", InputAction(sf::Keyboard::Space));

	input.SetInputActionMap(&inputActionMap);
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::OnLoad()
{
	GameObject::OnLoad();
}

void SpaceShip::Start()
{
	GameObject::Start();
}

void SpaceShip::Update()
{
	GameObject::Update();
	inputActionMap.UpdateKeyStatus();

	velocity = Vector2(input.GetHorizontalAxis() * moveSpeed, 0);

	rigidBody->AddForce(velocity);

	if (input.GetKeyDown("fire"))
	{
		Bullet* bullet = new Bullet(scene, "Bullet");
		bullet->SetPosition(position + Vector2(0, -100));

		scene->AddObject(bullet);
	}
}
