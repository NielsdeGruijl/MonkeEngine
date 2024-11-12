#pragma once

#include "../Components/SpriteRenderer.h"
#include "Object.h"

class GameObject : public Object
{
public:
	//SpriteRenderer sprite;
	std::shared_ptr<SpriteRenderer> spriteRenderer;

public:
	GameObject(std::string pID, std::string pFileName, int pPixelsPerUnit = 100);
	~GameObject();

	void Render(sf::RenderWindow* pRenderWindow) override;
	void Update() override;

	void SetPosition(const Vector2 pPosition);
	void SetScale(const Vector2 pScale);
	void SetScale(const float pScale);
	void SetOrigin(const Vector2 pOrigin);
};