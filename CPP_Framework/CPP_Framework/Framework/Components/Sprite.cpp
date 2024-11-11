#include "Sprite.h"

Sprite::Sprite(std::string pFileName, int pPixelsPerUnit)
	: spriteScale(CalculateSpriteScaleBasedOnPixelsPerUnit(pPixelsPerUnit))
{
	texture.loadFromFile("Assets/" + pFileName);
	sprite.setTexture(texture);
	SetScale(1);
}

Sprite::~Sprite()
{
}

void Sprite::SetColor(sf::Color pColor)
{
	sprite.setColor(pColor);
}

void Sprite::SetPosition(const Vector2 pPosition)
{
	sprite.setPosition(pPosition.ToSfVector());
}

void Sprite::SetScale(const Vector2 pScale)
{
	scale = pScale;
	
	sprite.setScale((scale * spriteScale).ToSfVector());
}

void Sprite::SetScale(const float pScale)
{
	SetScale(Vector2(pScale, pScale));
}

void Sprite::SetOrigin(const Vector2 pOrigin)
{
	sprite.setOrigin(Vector2(pOrigin.x * texture.getSize().x, pOrigin.y * texture.getSize().y).ToSfVector()); // Find a way to add vector operators with const vectors
}

void Sprite::Move(const Vector2 pVelocity)
{
	sprite.move(pVelocity.ToSfVector());
}

float Sprite::CalculateSpriteScaleBasedOnPixelsPerUnit(int pPixelsPerUnit)
{
	return (float)unitSize / pPixelsPerUnit;
}