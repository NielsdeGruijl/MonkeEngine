#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: obstacle("obstacle", "TransparentSquare.png", 160), obstacle2("obstacle2", "TransparentSquare.png", 160), enemy("enemy", "BlueSlime.png", 160), 
	  player("Player", "BlueSlime.png", 160)
{
	obstacle.SetPosition(Vector2(0, 360));
	obstacle.SetScale(Vector2(1, 720));
	obstacle.AddComponent<RigidBody>(&obstacle);

	//obstacle2.SetPosition(Vector2(0, 360));
	//obstacle2.SetScale(1);
	//obstacle2.AddComponent<AABBCollider>(obstacle2.GetSize(), obstacle2.position);

	player.SetPosition(Vector2(120, 360));

	enemy.SetPosition(Vector2(840, 360));
	enemy.AddComponent<RigidBody>(&enemy);
	enemy.GetComponent<RigidBody>()->gravity = 0;

	enemy.spriteRenderer->SetColor(sf::Color::Red);

	AddObject(&player);
	AddObject(&enemy);
	//AddObject(&obstacle);
	//AddObject(&obstacle2);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::UpdateScene()
{
	Scene::UpdateScene();
}
