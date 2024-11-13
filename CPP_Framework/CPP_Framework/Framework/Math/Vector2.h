#pragma once

#include <SFML/Graphics.hpp>

struct Vector2
{
	float x, y;

	Vector2();
	Vector2(float x, float y);
	Vector2(const sf::Vector2f* vector);
	~Vector2();

	float GetLength();
	void Normalize();
	sf::Vector2f ToSfVector() const;

	Vector2 Normalized();

	std::string printVector();

	// Multiplication operators
	Vector2 operator*(const float f1);
	Vector2 operator*=(const float f1);
	Vector2 operator*(const Vector2 v2);
	Vector2 operator*=(const Vector2 v2);

	// Addition operators
	Vector2 operator+(const Vector2 v2);
	Vector2 operator+=(const Vector2 v2);

	// Subtraction operators
	Vector2 operator-(const Vector2 v2);
	Vector2 operator-=(const Vector2 v2);

	Vector2 operator=(const Vector2 v2);
	bool operator==(const Vector2 v2);
	bool operator!=(const Vector2 v2);

	__declspec(property(get = Normalized)) Vector2 normalized;
};