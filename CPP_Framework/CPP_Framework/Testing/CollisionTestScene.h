#pragma once

#include "../Framework/Core/Scene.h"
#include "Player.h"
#include "Enemy.h"

class CollisionTestScene : public Scene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	void Update() override;

private:
	GameObject obstacle;
	GameObject obstacle2;
};