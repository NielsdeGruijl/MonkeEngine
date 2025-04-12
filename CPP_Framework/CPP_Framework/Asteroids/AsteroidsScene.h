#include "../Framework/Core/Scene.h"
#include "SpaceShip.h"
#include "AsteroidSpawner.h"

class AsteroidsScene : public Scene
{
public:
	AsteroidsScene();
	~AsteroidsScene();

	void UpdateScene() override;

private:
	SpaceShip spaceShip;
	AsteroidSpawner asteroidSpawner;

	GameObject cube;
};