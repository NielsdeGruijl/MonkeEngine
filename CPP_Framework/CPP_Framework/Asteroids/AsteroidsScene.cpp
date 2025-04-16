#include "AsteroidsScene.h"

AsteroidsScene::AsteroidsScene()
	: spaceShip(this, "spaceShip"), cube(this, "cube"), 
	asteroidSpawner(this, "asteroidSpawner")
{
	spaceShip.SetPosition(Vector2(640, 620));

	cube.SetPosition(Vector2(640, 100));
	cube.SetScale(Vector2(12.8f, 1));

	cube.AddComponent<RigidBody>(&cube);
	cube.GetComponent<RigidBody>()->gravity = 0;

	AddObject(&spaceShip);
	//AddObject(&cube);
	AddObject(&asteroidSpawner);
}

AsteroidsScene::~AsteroidsScene()
{
}

void AsteroidsScene::UpdateScene()
{
	Scene::UpdateScene();
}
