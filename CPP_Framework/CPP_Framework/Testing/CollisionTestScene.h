#pragma once

#include "../Framework/Core/Scene.h"
#include "PhysicsObject.h"
#include "Obstacle.h"

class CollisionTestScene : public Scene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	void UpdateScene() override;

private:
	PhysicsObject physicsObject;
	Obstacle obstacle;
};