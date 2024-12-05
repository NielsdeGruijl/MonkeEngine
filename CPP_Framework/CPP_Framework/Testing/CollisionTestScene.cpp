#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene()
	: obstacle("obstacle", "TransparentSquare.png", 160), obstacle2("obstacle2", "TransparentSquare.png", 160),
	  player("Player", "BlueSlime.png", 160), pawn("Pawn", "BlueSlime.png", 160), pawn1("Pawn1", "BlueSlime.png", 160),
	  a("a", "BlueSlime.png", 160)
{
	//pawn.SetPosition(Vector2(640, 960));
	//pawn.rigidBody->gravity = 0;
	//pawn.rigidBody->mass = 1;
	//pawn.rigidBody->drag = 0;
	//pawn.rigidBody->friction = 0;
	//
	//pawn1.SetPosition(Vector2(640, 360));
	//pawn1.rigidBody->gravity = 0;
	//pawn1.rigidBody->mass = 1;
	//pawn1.rigidBody->drag = 1;
	//pawn1.rigidBody->friction = 0;
	//
	//obstacle.SetPosition(Vector2(1230, 360));
	//obstacle.AddComponent<AABBCollider>(obstacle.GetSize(), obstacle.position);
	//
	//obstacle2.SetPosition(Vector2(0, 360));
	//obstacle2.SetScale(1);
	//obstacle2.AddComponent<AABBCollider>(obstacle2.GetSize(), obstacle2.position);
	//
	//player.SetPosition(Vector2(50, 360));
	//player.rigidBody->gravity = 0;
	//player.rigidBody->mass = 1;
	//player.rigidBody->drag = 1;
	//player.rigidBody->friction = 0;

	//AddObject(&pawn);
	//AddObject(&pawn1);
	//AddObject(&player);
	//AddObject(&obstacle);
	//AddObject(&obstacle2);

	a.AddComponent<RigidBody>(1, 1, 1);
	AddObject(&a);
}

CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::UpdateScene()
{
	Scene::UpdateScene();
}
