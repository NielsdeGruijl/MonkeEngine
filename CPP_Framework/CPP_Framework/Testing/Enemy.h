#pragma once
#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Components/SpriteRenderer.h"

class Enemy : public GameObject
{
public:
	Enemy(Scene* pScene, std::string pObjectId);
	~Enemy();

	void Update() override;

private:
	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<SpriteRenderer> sprite;
};