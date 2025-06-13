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

void SpriteRenderer::OnLoad()
{
	Component::OnLoad();
}

void SpriteRenderer::Update()
{
	Component::Update();

	if (accumulator > 0)
	{
		float lerpTime = Clamp(0, 1, accumulator / fixedDeltaTime);
		//Vector2 lastPosition = Vector2(sprite.getPosition().x, sprite.getPosition().y);
		Vector2 renderPosition = object->previousPosition + (object->position - object->previousPosition) * lerpTime;
		//Vector2 renderPosition = object->previousPosition.Lerp(object->position, lerpTime);
		SetPosition(renderPosition);

		if (object->GetID() == "Object25")
		{
			//std::cout << "sprite: " << (object->position - renderPosition).printVector();
			//std::cout << "object: " << object->position.printVector();
			std::cout << accumulator << "\n";
		}
	}


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

float SpriteRenderer::Clamp(float min, float max, float a)
{
	if (a < min)
		return min;
	if (a > max)
		return max;

	return a;
}