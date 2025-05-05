#include "PerformanceTestScene.h"
#include <sstream>

PerformanceTestScene::PerformanceTestScene()
{
	int objectId = 0;

	int totalObjects = 10;
	float scale = 0.5f;

	int startPos = 100 * scale;
	int verticalOffset = 110 * scale;
	int horizontalOffset = 50 * scale;

	for (size_t i = 0; i < totalObjects; i++)
	{
		std::ostringstream oss;
		objectId++;
		oss << "LeftObject" << objectId;
		std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
		leftObject->SetPosition(Vector2(200 + (i * horizontalOffset), startPos + (i * verticalOffset)));
		leftObject->moveDirection = -1;
		leftObject->SetScale(scale);
		AddObject(leftObject);
	}

	for (size_t i = 0; i < totalObjects; i++)
	{
		std::ostringstream oss;
		objectId++;
		oss << "LeftObject" << objectId;
		std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
		leftObject->SetPosition(Vector2(1080 - (i * horizontalOffset), startPos + (i * verticalOffset)));
		leftObject->moveDirection = 1;
		leftObject->SetScale(scale);
		AddObject(leftObject);
	}

	std::shared_ptr<GameObject> leftBoundary = std::make_shared<GameObject>(this, "LeftBoundary");
	leftBoundary->SetScale(Vector2(1, 100));
	leftBoundary->SetPosition(Vector2(-49, 360));
	leftBoundary->AddComponent<AABBCollider>(leftBoundary.get(), &leftBoundary->position);
	leftBoundary->AddComponent<SpriteRenderer>(leftBoundary.get(), "Cat.jpg", 236);
	AddObject(leftBoundary);

	std::shared_ptr<GameObject> rightBoundary = std::make_shared<GameObject>(this, "RightBoundary");
	rightBoundary->SetScale(Vector2(1, 100));
	rightBoundary->SetPosition(Vector2(1329, 360));
	rightBoundary->AddComponent<AABBCollider>(rightBoundary.get(), &rightBoundary->position);
	rightBoundary->AddComponent<SpriteRenderer>(rightBoundary.get(), "Cat.jpg", 236);
	AddObject(rightBoundary);
}

void PerformanceTestScene::UpdateScene()
{
	Scene::UpdateScene();
}