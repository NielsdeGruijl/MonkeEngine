#include "../Framework/Core/Scene.h"
#include "SpaceShip.h"

class AsteroidsScene : public Scene
{
public:
	AsteroidsScene();
	~AsteroidsScene();

	void UpdateScene() override;

private:
	SpaceShip spaceShip;

	GameObject cube;
};