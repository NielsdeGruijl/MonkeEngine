#include "TestScene.h"

TestScene::TestScene()
	: Scene(), staticObject("staticObject", "CatStare.jpg", 360), rectangleObject("rectangle", "OOcat.jpg", 3042), player("Player", "Cat.jpg", 236)
{
	InitializeObjectsInScene();
}

TestScene::~TestScene()
{
}

void TestScene::InitializeObjectsInScene()
{
	staticObject.SetPosition(Vector2(800, 400));
	AddObject(staticObject);

	AddObject(rectangleObject);

	player.SetPosition(Vector2(0, 400));
	AddObject(player);
}




            




      










