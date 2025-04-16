#include "AsteroidsScene.h"

AsteroidsScene::AsteroidsScene()
	/*: spaceShip(this, "spaceShip"), cube(this, "cube"), 
	asteroidSpawner(this, "asteroidSpawner")*/
{
	spaceShip = std::make_shared<SpaceShip>(this, "spaceShip");
	spaceShip->SetPosition(Vector2(640, 620));	

	asteroidSpawner = std::make_shared<AsteroidSpawner>(this, "asteroidSpawner");

	AddObject(spaceShip);
	AddObject(asteroidSpawner);
}

AsteroidsScene::~AsteroidsScene()
{
}

void AsteroidsScene::UpdateScene()
{
	Scene::UpdateScene();
}
