#pragma once

#include "../Framework/Core/Scene.h"
#include "Player.h"

class CollisionTestScene : public Scene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	void UpdateScene() override;

private:
	GameObject obstacle;
	GameObject obstacle2;

	Player player;

	GameObject enemy;
};