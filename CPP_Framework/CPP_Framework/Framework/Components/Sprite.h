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
	Sprite(std::string fileName, int pixelsPerUnit);
	~Sprite();

	void SetColor(sf::Color color);
	void SetPosition(const Vector2 position);
	void SetScale(const Vector2 scale);
	void SetScale(const float scale);
	void SetOrigin(const Vector2 origin);
	
	void Move(const Vector2 velocity);

	float CalculateSpriteScaleBasedOnPixelsPerUnit(int pixelsPerUnit);

private:
	sf::Texture texture;
	const float spriteScale;
	Vector2 scale;
};