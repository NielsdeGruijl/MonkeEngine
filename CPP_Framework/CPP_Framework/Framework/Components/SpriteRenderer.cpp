#include "SpriteRenderer.h"

#include "../Objects/Object.h"

SpriteRenderer::SpriteRenderer(Object* pObject, std::string pFileName, int pPixelsPerUnit)
	: Component(pObject), spriteScale(CalculateSpriteScaleBasedOnPixelsPerUnit(pPixelsPerUnit))
{
	texture.loadFromFile("Assets/" + pFileName);
	sprite.setTexture(texture);
	SetScale(1);
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update()
{
	Component::Update();
	sprite.setPosition(object->position.ToSfVector());
}

void SpriteRenderer::SetColor(sf::Color pColor)
{
	sprite.setColor(pColor);
}

void SpriteRenderer::SetPosition(const Vector2 pPosition)
{
	sprite.setPosition(pPosition.ToSfVector());
}

void SpriteRenderer::SetScale(const Vector2 pScale)
{
	scale = pScale;
	sprite.setScale((scale * spriteScale).ToSfVector());
}

void SpriteRenderer::SetScale(const float pScale)
{
	SetScale(Vector2(pScale, pScale));
}

void SpriteRenderer::SetOrigin(const Vector2 pOrigin)
{
	sprite.setOrigin(Vector2(pOrigin.x * texture.getSize().x, pOrigin.y * texture.getSize().y).ToSfVector()); // Find a way to add vector operators with const vectors
}

void SpriteRenderer::Move(const Vector2 pVelocity)
{
	sprite.move(pVelocity.ToSfVector());
}

float SpriteRenderer::CalculateSpriteScaleBasedOnPixelsPerUnit(int pPixelsPerUnit)
{
	return (float)unitSize / pPixelsPerUnit;
}