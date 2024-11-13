#pragma once

#include "../Framework/Core/Scene.h"
#include "../Framework/Objects/GameObject.h"
#include "PhysicsObject.h"
#include "Player.h"

class CollisionTestScene : public Scene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	void UpdateScene() override;

private:
	PhysicsObject physicsObject;
	PhysicsObject physicsObject2;
	GameObject obstacle;
	Player player;
};