#include "SpriteRenderer.h"

#include "../Objects/GameObject.h"
#include <cmath>

extern float fixedDeltaTime;
extern float accumulator;

SpriteRenderer::SpriteRenderer(GameObject* pObject, std::string pFileName, int pPixelsPerUnit)
	: Component(pObject), spriteScale(CalculateSpriteScaleBasedOnPixelsPerUnit(pPixelsPerUnit))
{
	SetScale(object->scale);

	texture.loadFromFile("Assets/" + pFileName);
	sprite.setTexture(texture);

	SetOrigin(Vector2(0.5f, 0.5f)); 
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update()
{
	Component::Update();

	Vector2 renderPosition = object->previousPosition.Lerp(object->position, accumulator / fixedDeltaTime);
	SetPosition(renderPosition);

	//SetPosition(object->position);
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

