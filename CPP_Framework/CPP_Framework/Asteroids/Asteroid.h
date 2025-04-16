#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"

class Asteroid : public GameObject
{
public:
	Asteroid(Scene* pScene, std::string pId, std::string pFileName, int pPixelsPerUnit);
	~Asteroid();

	std::shared_ptr<RigidBody> rigidBody;

private:
	void Start() override;
	void Update() override;

	void OnCollisionEnter() override;
	void OnParamCollisionEnter(Object* object) override;
};