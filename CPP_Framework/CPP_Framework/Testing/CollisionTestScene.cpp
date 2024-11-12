#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: physicsObject("PhysicsObject", "BlueSlime.png", 160), obstacle("Obstacle", "TransparentSquare.png", 160)
{
	physicsObject.SetPosition(Vector2(50, 360));
	physicsObject.AddComponent<AABBCollider>(physicsObject.GetSize(), physicsObject.position);
	AddObject(&physicsObject);

	obstacle.SetPosition(Vector2(640, 360));
	obstacle.SetScale(2);
	obstacle.AddComponent<AABBCollider>(obstacle.GetSize(), physicsObject.position);
	AddObject(&obstacle);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::UpdateScene()
{
	Scene::UpdateScene();

	if (physicsObject.GetComponent<AABBCollider>()->CheckCollision(obstacle.GetComponent<AABBCollider>()))
	{
		std::cout << "collision \n";
	}
}
