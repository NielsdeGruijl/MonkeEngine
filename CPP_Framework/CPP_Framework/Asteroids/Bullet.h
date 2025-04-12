#include <SFML/Graphics.hpp>

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"

class Bullet : public GameObject
{
public:
	Bullet(Scene* pScene, std::string pObjectId, std::string pSpriteFileName, int pPixelsPerUnit);
	~Bullet();

	std::shared_ptr<RigidBody> rigidBody;

private:
	void Start() override;
	void Update() override;

	void Destroy();

	void OnCollisionEnter() override;

	sf::Clock lifeTime;

	float moveSpeed;
};