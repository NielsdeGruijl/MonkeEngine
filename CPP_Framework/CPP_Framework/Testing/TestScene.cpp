#include "TestScene.h"

TestScene::TestScene()
	: Scene(), staticObject(this, "staticObject", "TestSquare.png", 160), rectangleObject(this, "rectangle", "OOcat.jpg", 3024), player(this, "player", "Cat.jpg", 236)
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