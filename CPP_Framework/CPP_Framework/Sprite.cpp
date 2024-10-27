#include "Sprite.h"

Sprite::Sprite(std::string fileName, int pixelsPerUnit)
	: spriteScale(CalculateSpriteScaleBasedOnPixelsPerUnit(pixelsPerUnit)), scale(1, 1)
{
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	SetScale(1);
}

Sprite::~Sprite()
{
}

void Sprite::SetColor(sf::Color color)
{
	sprite.setColor(color);
}

void Sprite::SetPosition(const Vector2 position)
{
	sprite.setPosition(position.ToSfVector());
}

void Sprite::SetScale(const Vector2 _scale)
{
	scale = _scale;
	
	sprite.setScale((scale * spriteScale).ToSfVector());
}

void Sprite::SetScale(const float _scale)
{
	scale *= scale;

	sprite.setScale((scale * spriteScale).ToSfVector());
}


void Sprite::Move(const Vector2 velocity)
{
	sprite.move(velocity.ToSfVector());
}

float Sprite::CalculateSpriteScaleBasedOnPixelsPerUnit(int pixelsPerUnit)
{
	return (float)unitSize / pixelsPerUnit;
}