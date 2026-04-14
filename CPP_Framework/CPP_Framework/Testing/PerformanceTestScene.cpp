#include "PerformanceTestScene.h"
#include <sstream>

PerformanceTestScene::PerformanceTestScene()
{
	int objectId = 0;

	int rows = 10;
	int columns = 40;

	float scale = .3f;

	int xOffset = 50;
	int yOffset = 1440 / rows;

	float gridWidth = columns * xOffset;

	int xStart = 1280 - (gridWidth * 0.5f);
	int yStart = yOffset * 0.5f;

	float moveDirection = 1;

	for (int i = 0; i < rows; i++)
	{
		if (i % 3 == 0)
			moveDirection = 0.5f;
		else if (i % 2 == 0)
			moveDirection = 0.33f;
		else
			moveDirection = 1;

		for (int j = 0; j < columns; j++)
		{
			std::ostringstream oss;
			objectId++;
			oss << "Object" << objectId;
			moveDirection *= -1;

			std::shared_ptr<LeftObject> leftObject = std::make_shared<LeftObject>(this, oss.str());
			leftObject->SetPosition(Vector2(xStart + (j * xOffset), yStart + (i * yOffset)));
			leftObject->moveDirection = moveDirection;
			leftObject->SetScale(scale);
			std::shared_ptr<SpriteRenderer> sprite = leftObject->GetComponent<SpriteRenderer>();
			sprite->SetPosition(leftObject->position);

			objects.push_back(leftObject);

			if(j % 2 == 0)
				leftObject->GetComponent<SpriteRenderer>()->sprite.setColor(sf::Color::Red);

			AddObject(leftObject);
		}
	}

	std::shared_ptr<GameObject> leftBoundary = std::make_shared<GameObject>(this, "LeftBoundary");
	leftBoundary->SetScale(Vector2(1, 15));
	leftBoundary->SetPosition(Vector2(xStart - 49 - xOffset, 720));
	leftBoundary->AddComponent<AABBCollider>(leftBoundary.get(), &leftBoundary->position);
	leftBoundary->AddComponent<SpriteRenderer>(leftBoundary.get(), "TransparentSquare.png", 160);
	AddObject(leftBoundary);

	std::shared_ptr<GameObject> rightBoundary = std::make_shared<GameObject>(this, "RightBoundary");
	rightBoundary->SetScale(Vector2(1, 15));
	rightBoundary->SetPosition(Vector2(xStart + gridWidth + 49, 720));
	rightBoundary->AddComponent<AABBCollider>(rightBoundary.get(), &rightBoundary->position);
	rightBoundary->AddComponent<SpriteRenderer>(rightBoundary.get(), "TransparentSquare.png", 160);
	AddObject(rightBoundary);
}