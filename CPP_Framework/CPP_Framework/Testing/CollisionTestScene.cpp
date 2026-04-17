#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: obstacle(this, "obstacle"), obstacle2(this, "obstacle2")
{
	obstacle.SetPosition(Vector2(0, 360));
	obstacle.SetScale(Vector2(1, 720));
	obstacle.AddComponent<RigidBody>(&obstacle);

	//obstacle2.SetPosition(Vector2(0, 360));
	//obstacle2.SetScale(1);
	//obstacle2.AddComponent<AABBCollider>(obstacle2.GetSize(), obstacle2.position);

	player = std::make_shared<Player>(this, "Player");
	player->SetPosition(Vector2(2560,720));

	enemy = std::make_shared<Enemy>(this, "Enemy");
	enemy->SetPosition(Vector2(2440, 720));

	AddObject(player);
	AddObject(enemy);
	//AddObject(&obstacle);
	//AddObject(&obstacle2);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}
