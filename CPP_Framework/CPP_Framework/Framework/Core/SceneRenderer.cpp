#include "SceneRenderer.h"

SceneRenderer::SceneRenderer()
{
}

SceneRenderer::~SceneRenderer()
{
}

void SceneRenderer::AddSprite(std::weak_ptr<SpriteRenderer> pSprite)
{
	spriteRenderers.push_back(pSprite);
}

void SceneRenderer::RemoveSprite(std::weak_ptr<SpriteRenderer> pSprite)
{
	
}

void SceneRenderer::RenderSprites(sf::RenderWindow* renderWindow)
{
	for (std::weak_ptr<SpriteRenderer> spriteRenderer : spriteRenderers)
	{
		if (auto tSpriteRenderer = spriteRenderer.lock())
		{
			renderWindow->draw(tSpriteRenderer->sprite);
		}
	}
}