
// GameObjects are static objects that can't move.

#pragma once

#include "../Components/Sprite.h"
#include "Object.h"

class GameObject : public Object
{
public:
	Sprite sprite;

public:
	GameObject(std::string ID, std::string fileName, int pixelsPerUnit = 100);
	~GameObject();

	void Render(sf::RenderWindow* renderWindow) override;
	void Update() override;

	void SetPosition(const Vector2 pos);
	void SetScale(const Vector2 size);
	void SetOrigin(const Vector2 origin);
};