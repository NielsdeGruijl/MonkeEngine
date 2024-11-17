#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: obstacle("obstacle", "TransparentSquare.png", 160), obstacle2("obstacle2", "TransparentSquare.png", 160),
	   player("Player", "BlueSlime.png", 160), pawn("Pawn", "BlueSlime.png", 160), pawn1("Pawn1", "BlueSlime.png", 160)
{
	pawn.SetPosition(Vector2(400, 360));
	pawn.controller->SetVelocity(Vector2(250, 0));
	pawn.controller->gravity = 0;
	pawn.controller->bounciness = 1;

	pawn1.SetPosition(Vector2(1230, 360));
	pawn1.controller->SetVelocity(Vector2(-250, 0));
	pawn1.controller->gravity = 0;
	pawn1.controller->drag = 0;
	pawn1.controller->friction = 0;
	//pawn1.controller->bounciness = 1;

	obstacle.SetPosition(Vector2(1280, 360));
	obstacle.SetScale(2);
	obstacle.AddComponent<AABBCollider>(obstacle.GetSize(), obstacle.position);

	obstacle2.SetPosition(Vector2(0, 360));
	obstacle2.SetScale(2);
	obstacle2.AddComponent<AABBCollider>(obstacle2.GetSize(), obstacle2.position);

	player.SetPosition(Vector2(50, 360));
	player.controller->friction = 0;
	//player.controller->bounciness = 1;

	//AddObject(&pawn);
	AddObject(&pawn1);
	AddObject(&player);
	//AddObject(&obstacle);
	//AddObject(&obstacle2);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::UpdateScene()
{
	Scene::UpdateScene();
	collisionChecker.CheckCollisions();
	//collisionChecker.CheckPawnToPawn();
}
