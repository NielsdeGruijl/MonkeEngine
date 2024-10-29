#include "Vector2.h"
#include <math.h>
#include <sstream>

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(const sf::Vector2f* vector)
{
	this->x = vector->x;
	this->y = vector->y;
}

Vector2::~Vector2()
{
}

float Vector2::GetLength()
{
	return sqrtf(x * x + y * y);
}

void Vector2::Normalize()
{
	float length = GetLength();

	x /= length;
	y /= length;
}

Vector2 Vector2::Normalized()
{
	float length = GetLength();

	return Vector2(x /= length, y /= length);
}

sf::Vector2f Vector2::ToSfVector() const
{
	return sf::Vector2f(x, y);
}

std::string Vector2::printVector()
{
	std::ostringstream oss;
	oss << "(" << x << ", " << y << ")\n";
	
	return oss.str();
}

// Multiplication operators

Vector2 Vector2::operator*(const float f1)
{
	return Vector2(x * f1, y * f1);
}
Vector2 Vector2::operator*=(const float f1)
{
	x *= f1;
	y *= f1;

	return Vector2(x, y);
}
Vector2 Vector2::operator*(const Vector2 v2)
{
	return Vector2(x * v2.x, y * v2.y);
}
Vector2 Vector2::operator*=(const Vector2 v2)
{
	x *= v2.x;
	y *= v2.y;

	return Vector2(x, y);
}

// Addition operators

Vector2 Vector2::operator+(const Vector2 v2)
{
	return Vector2(x + v2.x, y + v2.y);
}
Vector2 Vector2::operator+=(const Vector2 v2)
{
	x += v2.x;
	y += v2.y;

	return Vector2(x, y);
}

// Subtraction operators

Vector2 Vector2::operator-(const Vector2 v2)
{
	return Vector2(x - v2.x, y - v2.y);
}
Vector2 Vector2::operator-=(const Vector2 v2)
{
	x -= v2.x;
	y -= v2.y;

	return Vector2(x, y);
}

//Assignment operators
Vector2 Vector2::operator=(const Vector2 v2)
{
	x = v2.x;
	y = v2.y;

	return Vector2(x, y);
}
