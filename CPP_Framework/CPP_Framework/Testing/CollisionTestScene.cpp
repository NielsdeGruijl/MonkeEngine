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

	std::shared_ptr<Player> player = std::make_shared<Player>(this, "Player");
	player->SetPosition(Vector2(120, 360));

	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(this, "Enemy");
	enemy->SetPosition(Vector2(840, 360));

	AddObject(player);
	AddObject(enemy);
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
