#pragma once

#include "Scene.h"
#include "Player.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void InitializeObjectsInScene() override;

private:
	GameObject staticObject;
	GameObject rectangleObject;
};