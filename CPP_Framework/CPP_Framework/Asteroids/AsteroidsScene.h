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
	std::shared_ptr<SpaceShip> spaceShip;
	std::shared_ptr<AsteroidSpawner> asteroidSpawner;
};