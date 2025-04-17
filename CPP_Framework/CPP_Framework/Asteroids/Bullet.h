#include <SFML/Graphics.hpp>

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Components/SpriteRenderer.h"

class Bullet : public GameObject
{
public:
	Bullet(Scene* pScene, std::string pObjectId);
	~Bullet();

	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<SpriteRenderer> sprite;

private:
	void Start() override;
	void Update() override;

	void OnCollisionEnter(GameObject* object) override;

	sf::Clock lifeTime;

	float moveSpeed;
};