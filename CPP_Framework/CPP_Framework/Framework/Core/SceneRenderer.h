#include <SFML/Graphics.hpp>
#include "../Components/SpriteRenderer.h"

class SceneRenderer
{
public:
	SceneRenderer();
	~SceneRenderer();

	void AddSprite(std::weak_ptr<SpriteRenderer> pSprite);
	void RemoveSprite(std::weak_ptr<SpriteRenderer> pSprite);

	void RenderSprites(sf::RenderWindow* renderWindow);

private:
	std::vector<std::weak_ptr<SpriteRenderer>> spriteRenderers;
};