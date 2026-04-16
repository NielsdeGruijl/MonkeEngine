#pragma once

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Components/SpriteRenderer.h"

class LeftObject : public GameObject
{
public:
	LeftObject(Scene* pScene, std::string pObjectId);

	void OnLoad() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;

	void OnCollisionEnter(std::weak_ptr<AABBCollider> pOtherCollider) override;

public:
	float moveDirection;
	float moveSpeed;

private:
	std::shared_ptr<RigidBody> rigidBody;
};