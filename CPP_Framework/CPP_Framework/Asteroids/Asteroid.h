#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Components/SpriteRenderer.h"

class Asteroid : public GameObject
{
public:
	Asteroid(Scene* pScene, std::string pId);
	~Asteroid();

	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<SpriteRenderer> sprite;

private:
	void Start() override;
	void Update() override;

	void OnCollisionEnter(GameObject* pObject) override;
};