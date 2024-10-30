#pragma once

#include "../Framework/Core/Scene.h"
#include "Player.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

private:
	GameObject staticObject;
	GameObject rectangleObject;
	Player player;
};