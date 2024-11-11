#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"

extern const int unitSize;

class Sprite
{
public:
	sf::Sprite sprite;

public:
	Sprite(std::string pFileName, int pPixelsPerUnit = 100);
	~Sprite();

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