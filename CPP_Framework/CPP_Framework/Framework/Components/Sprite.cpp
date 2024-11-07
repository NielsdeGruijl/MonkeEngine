#include "Sprite.h"

Sprite::Sprite(std::string fileName, int pixelsPerUnit)
	: spriteScale(CalculateSpriteScaleBasedOnPixelsPerUnit(pixelsPerUnit)), scale(1, 1)
{
	name = fileName;
	texture.loadFromFile("Assets/" + fileName);
	sprite.setTexture(texture);
	originalSize = Vector2(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
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

void Sprite::SetOrigin(const Vector2 origin)
{
	sprite.setOrigin(Vector2(origin.x * texture.getSize().x, origin.y * texture.getSize().y).ToSfVector()); // Find a way to add vector operators with const vectors
}

void Sprite::Move(const Vector2 velocity)
{
	sprite.move(velocity.ToSfVector());
}

float Sprite::CalculateSpriteScaleBasedOnPixelsPerUnit(int pixelsPerUnit)
{
	return (float)unitSize / pixelsPerUnit;
}