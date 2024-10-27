
// GameObjects are static objects that can't move.

#pragma once

#include "Object.h"
#include "Sprite.h"

class GameObject : public Object
{
public:
	Sprite sprite;

public:
	GameObject(std::string ID, std::string fileName, int pixelsPerUnit = 100);
	~GameObject();

	void Render(sf::RenderWindow* window) override;
	void Update() override;

	void SetPosition(const Vector2 pos);
	void SetScale(const Vector2 size);
};