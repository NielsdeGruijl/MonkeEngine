#include "AsteroidsScene.h"

AsteroidsScene::AsteroidsScene()
	: spaceShip(this, "spaceShip", "BlueSlime.png", 160), cube(this, "cube", "Cat.jpg", 236)
{
	spaceShip.SetPosition(Vector2(640, 620));

	cube.SetPosition(Vector2(640, 100));
	cube.SetScale(Vector2(12.8f, 1));

	cube.AddComponent<RigidBody>(&cube);
	cube.GetComponent<RigidBody>()->gravity = 0;

	AddObject(&spaceShip);
	AddObject(&cube);
}

AsteroidsScene::~AsteroidsScene()
{
}

void AsteroidsScene::UpdateScene()
{
	Scene::UpdateScene();
}
