#pragma once

#include "../Framework/Core/Scene.h"

#include "SpaceShip.h"
#include "Bullet.h"

#include "Powerups/BigBulletPowerup.h"


SpaceShip::SpaceShip(Scene* pScene, std::string pId)
	: GameObject(pScene, pId), input()
{
	bulletSizeMultiplier = 1;
	moveSpeed = 5;

	rigidBody = AddComponent<RigidBody>(this);
	rigidBody->gravity = 0;
	rigidBody->yConstraint = true;

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
		std::shared_ptr<Bullet> tBullet = std::make_shared<Bullet>(scene, "Bullet");
		tBullet->SetPosition(position + Vector2(0, -100));
		tBullet->SetScale(tBullet->scale * bulletSizeMultiplier);

		scene->AddObject(tBullet);
	}
}

void SpaceShip::OnCollisionEnter(GameObject* object)
{
	std::shared_ptr<BasePowerup> powerup;
	if (object->TryGetComponent<BasePowerup>(powerup))
	{
		bulletSizeMultiplier = powerup->bulletSizeMultiplier;
		powerup->object->Destroy();
	}
}