#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: obstacle(this, "obstacle"), obstacle2(this, "obstacle2"), enemy(this, "enemy"), 
	  player(this, "Player")
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
