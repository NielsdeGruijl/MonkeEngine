#include "PerformanceTestScene.h"
#include <sstream>

PerformanceTestScene::PerformanceTestScene()
{
	int objectId = 0;

	int totalObjects = 10;

	int rows = 10;
	int columns = 10;

	float scale = .3f;

	int xOffset = 1280 / columns;
	int yOffset = 720 / rows;

	int xStart = xOffset / 2;
	int yStart = yOffset / 2;

	for (int i = 0; i < rows; i++)
	{
		float moveDirection = 1;
		for (int j = 0; j < columns; j++)
		{
			std::ostringstream oss;
			objectId++;
			oss << "LeftObject" << objectId;
			moveDirection *= -1;

			std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
			leftObject->SetPosition(Vector2(xStart + (j * xOffset), yStart + (i * yOffset)));
			leftObject->moveDirection = moveDirection;
			leftObject->SetScale(scale);
			AddObject(leftObject);
		}
	}

	std::shared_ptr<GameObject> leftBoundary = std::make_shared<GameObject>(this, "LeftBoundary");
	leftBoundary->SetScale(Vector2(10, 100));
	leftBoundary->SetPosition(Vector2(-499, 360));
	leftBoundary->AddComponent<AABBCollider>(leftBoundary.get(), &leftBoundary->position);
	leftBoundary->AddComponent<SpriteRenderer>(leftBoundary.get(), "Cat.jpg", 236);
	AddObject(leftBoundary);

	std::shared_ptr<GameObject> rightBoundary = std::make_shared<GameObject>(this, "RightBoundary");
	rightBoundary->SetScale(Vector2(10, 100));
	rightBoundary->SetPosition(Vector2(1280 + 499, 360));
	rightBoundary->AddComponent<AABBCollider>(rightBoundary.get(), &rightBoundary->position);
	rightBoundary->AddComponent<SpriteRenderer>(rightBoundary.get(), "Cat.jpg", 236);
	AddObject(rightBoundary);
}

void PerformanceTestScene::UpdateScene()
{
	Scene::UpdateScene();
}