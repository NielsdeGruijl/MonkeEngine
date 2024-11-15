#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: physicsObject("PhysicsObject", "BlueSlime.png", 160), obstacle("obstacle", "TransparentSquare.png", 160), physicsObject2("physicsObject2", "TestSquare.png", 160), 
	  player("Player", "BlueSlime.png", 160)
{
	physicsObject.SetPosition(Vector2(50, 360));
	physicsObject.AddComponent<AABBCollider>(physicsObject.GetSize(), physicsObject.position);
	physicsObject.controller->SetVelocity(Vector2(250, 0));
	physicsObject.controller->drag = 0;
	physicsObject.controller->gravity = 0;

	physicsObject2.SetPosition(Vector2(1230, 360));
	physicsObject2.AddComponent<AABBCollider>(physicsObject.GetSize(), physicsObject2.position);
	physicsObject2.controller->SetVelocity(Vector2(-250, 0));
	physicsObject2.controller->drag = 0;
	physicsObject2.controller->gravity = 0;

	obstacle.SetPosition(Vector2(680, 360));
	obstacle.SetScale(2);
	obstacle.AddComponent<AABBCollider>(obstacle.GetSize(), physicsObject.position);

	player.SetPosition(Vector2(50, 360));
	player.controller->friction = 0.5f;
	player.AddComponent<AABBCollider>(player.GetSize(), player.position);
	player.controller->collider = player.GetComponent<AABBCollider>();

	//std::vector<std::shared_ptr<CharacterController>> controllers = player.GetComponents<CharacterController>();

	//std::cout << controllers.size() << "\n";
	
	//AddObject(&physicsObject);
	//AddObject(&physicsObject2);
	AddObject(&player);
	AddObject(&obstacle);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::UpdateScene()
{
	Scene::UpdateScene();
	collisionChecker.CheckCollisions();

	//std::cout << player.GetComponent<AABBCollider>()->position.printVector();

	//collisionChecker.CheckSweptCollisions();

	//if (physicsObject.GetComponent<AABBCollider>()->CheckCollision(obstacle.GetComponent<AABBCollider>()))
	//{
	//	std::cout << "collision \n";
	//}
	
}
