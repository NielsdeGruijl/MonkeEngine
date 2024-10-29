#include "TestScene.h"

TestScene::TestScene()
	: Scene(), staticObject("staticObject", "CatStare.jpg", 360), rectangleObject("rectangle", "OOcat.jpg", 3042)
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
}




            




      










