#pragma once

#include <SFML/Graphics.hpp>

class Vector2
{
private:

public:
	float x, y;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(sf::Vector2f* vector);
	~Vector2();

	float GetLength();
	void Normalize();
	sf::Vector2f ToSfVector() const;

	Vector2 operator*(float f1);
	Vector2 operator+(Vector2 v2);
	Vector2 operator-(Vector2 v2);
};