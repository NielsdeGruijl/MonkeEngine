#pragma once
#include "AsteroidSpawner.h"
#include "../Framework/Core/Scene.h"

AsteroidSpawner::AsteroidSpawner(Scene* scene, std::string pId, std::string fileName, int pPixelsPerInch)
	: GameObject(scene, pId, fileName, pPixelsPerInch)
{
	leftBound = 50;
	rightBound = 1180;

	cooldown = 3;

	spriteRenderer->SetColor(sf::Color::Transparent);
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
		SpawnAsteroid();
		cooldownTimer.restart();
	}
}

void AsteroidSpawner::SpawnAsteroid()
{
	Asteroid* asteroid = new Asteroid(scene, "asteroid", "Cat.jpg", 236);
	float xPosition = std::rand() % rightBound + leftBound;
	asteroid->SetPosition(Vector2(xPosition, -50));
	scene->AddObject(asteroid);
}
