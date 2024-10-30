#include "TestScene.h"

TestScene::TestScene()
	: Scene(), staticObject("staticObject", "CatStare.jpg", 360), rectangleObject("rectangle", "OOcat.jpg", 3042), player("player", "cat.jpg", 236)
{
    staticObject.SetPosition(Vector2(600, 300));
    AddObject(&staticObject);

    rectangleObject.SetScale(Vector2(2, 5));
    AddObject(&rectangleObject);

    AddObject(&player);
}

TestScene::~TestScene()
{
}




            




      










