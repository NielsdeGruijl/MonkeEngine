#pragma once
#include "AsteroidSpawner.h"
#include "../Framework/Core/Scene.h"

AsteroidSpawner::AsteroidSpawner(Scene* scene, std::string pId)
	: GameObject(scene, pId)
{
	leftBound = 50;
	rightBound = 1180;

	cooldown = 3;
}

AsteroidSpawner::~AsteroidSpawner()
{
}

void AsteroidSpawner::Start()
{
	GameObject::Start();

	SpawnAsteroid();
}

void AsteroidSpawner::Update()
{
	GameObject::Update();
	
	if (cooldownTimer.getElapsedTime().asSeconds() > cooldown)
	{
		if (std::rand() % 100 < 10)
			SpawnPowerup();
		else
			SpawnAsteroid();

		cooldownTimer.restart();
	}
}

void AsteroidSpawner::SpawnAsteroid()
{
	std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(scene, "asteroid");
	float xPosition = std::rand() % rightBound + leftBound;
	asteroid->SetPosition(Vector2(xPosition, -50));
	scene->AddObject(asteroid);
}

void AsteroidSpawner::SpawnPowerup()
{
	std::shared_ptr<PowerupObject> powerup = std::make_shared<PowerupObject>(scene, "powerup");
	float xPosition = std::rand() % rightBound + leftBound;
	powerup->SetPosition(Vector2(xPosition, -50));
	scene->AddObject(powerup);
}