#include "TestScene.h"

TestScene::TestScene()
	: Scene(), staticObject("staticObject", "TestSquare.png", 160), rectangleObject("rectangle", "OOcat.jpg", 3024), player("player", "Cat.jpg", 236)
{
    staticObject.SetPosition(Vector2(1280, 720));
    AddObject(&staticObject);

    //rectangleObject.SetScale(Vector2(2, 5));
    rectangleObject.SetPosition(Vector2(0, 720));
    AddObject(&rectangleObject);
    
    AddObject(&player);
}

TestScene::~TestScene()
{
}