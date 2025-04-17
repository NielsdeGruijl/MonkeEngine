#include "Asteroid.h"
#include "Powerups/PowerupObject.h"
#include <SFML/Graphics.hpp>

class AsteroidSpawner : public GameObject
{
public:
	AsteroidSpawner(Scene* scene, std::string pId);
	~AsteroidSpawner();

private:
	void Start() override;
	void Update() override;

	void SpawnAsteroid();
	void SpawnPowerup();

	sf::Clock cooldownTimer;

	int leftBound, rightBound;
	float cooldown;
};