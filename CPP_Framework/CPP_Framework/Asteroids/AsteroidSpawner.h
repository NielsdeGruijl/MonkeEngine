#include "Asteroid.h"
#include <SFML/Graphics.hpp>

class AsteroidSpawner : public GameObject
{
public:
	AsteroidSpawner(Scene* scene, std::string pId, std::string fileName, int pPixelsPerInch);
	~AsteroidSpawner();

private:
	void Start() override;
	void Update() override;

	void SpawnAsteroid();

	sf::Clock cooldownTimer;

	int leftBound, rightBound;
	float cooldown;
};