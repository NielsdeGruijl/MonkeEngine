#include "PerformanceTestScene.h"
#include <sstream>

PerformanceTestScene::PerformanceTestScene()
{
	int objectId = 0;

	for (size_t i = 0; i < 5; i++)
	{
		std::ostringstream oss;
		objectId++;
		oss << "LeftObject" << objectId;
		std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
		leftObject->SetPosition(Vector2(200, 100 + (i * 105)));
		leftObject->moveDirection = 1;
		AddObject(leftObject);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::ostringstream oss;
		objectId++;
		oss << "LeftObject" << objectId;
		std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
		leftObject->SetPosition(Vector2(1080, 100 + (i * 105)));
		leftObject->moveDirection = -1;
		AddObject(leftObject);
	}
}

void PerformanceTestScene::UpdateScene()
{
	Scene::UpdateScene();
}