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
	SpriteRenderer(std::string pFileName, int pPixelsPerUnit = 100);
	~SpriteRenderer();

	void Update() override;

	void SetColor(sf::Color pColor);
	void SetPosition(const Vector2 pPosition);
	void SetScale(const Vector2 pScale);
	void SetScale(const float pScale);
	void SetOrigin(const Vector2 pOrigin);
	
	void Move(const Vector2 pVelocity);

	float CalculateSpriteScaleBasedOnPixelsPerUnit(int pPixelsPerUnit);

private:
	sf::Texture texture;
	Vector2 scale;

	const float spriteScale;
};