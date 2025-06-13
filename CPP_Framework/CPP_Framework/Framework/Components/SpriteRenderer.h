#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "Component.h"

extern const int unitSize;

class SpriteRenderer : public Component
{
public:
	sf::Sprite sprite;

public:
	SpriteRenderer(GameObject* pObject, std::string pFileName, int pPixelsPerUnit = 160);
	~SpriteRenderer();

	void OnLoad() override;

	void Update() override;

	void SetColor(sf::Color pColor);
	void SetPosition(const Vector2 pPosition);
	void SetScale(const Vector2 pScale);
	void SetOrigin(const Vector2 pOrigin);
	
	void Move(const Vector2 pVelocity);

	float CalculateSpriteScaleBasedOnPixelsPerUnit(int pPixelsPerUnit);

private:
	sf::Texture texture;
	Vector2 scale;

	const float spriteScale;

private:
	float Clamp(float min, float max, float a);
};