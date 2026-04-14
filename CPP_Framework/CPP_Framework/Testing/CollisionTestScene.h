#pragma once

#include "../Framework/Core/Scene.h"
#include "Player.h"
#include "Enemy.h"

class CollisionTestScene : public Scene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	void Update(float deltaTime) override;

private:
	GameObject obstacle;
	GameObject obstacle2;

	std::shared_ptr<Player> player;
	std::shared_ptr<Enemy> enemy;
};