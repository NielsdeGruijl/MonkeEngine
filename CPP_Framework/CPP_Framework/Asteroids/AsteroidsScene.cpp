#include "AsteroidsScene.h"

AsteroidsScene::AsteroidsScene()
	: spaceShip(this, "spaceShip", "BlueSlime.png", 160)
{
	spaceShip.SetPosition(Vector2(640, 620));

	AddObject(&spaceShip);
}

AsteroidsScene::~AsteroidsScene()
{
}

void AsteroidsScene::UpdateScene()
{
	Scene::UpdateScene();
}
