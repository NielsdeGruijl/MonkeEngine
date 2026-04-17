#pragma once

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"
#include "../Framework/Input/InputActionMap.h"
#include "../Framework/Input/InputHandler.h"

class Player : public GameObject
{
public:
	Player(Scene* pScene, std::string pObjectId);
	~Player();

	void OnLoad() override;
	void Start() override;
	void Update(float deltaTime) override;

	void SetActionMap(InputActionMap* pMap);

	std::shared_ptr<RigidBody> rigidBody;

protected:
	void OnCollisionEnter(std::weak_ptr<AABBCollider> pOtherCollider) override;
	void OnCollisionStay(std::weak_ptr<AABBCollider> pOtherCollider) override;
	void OnCollisionExit(std::weak_ptr<AABBCollider> pOtherCollider) override;

private:
	InputActionMap defaultInputActionMap;
	InputHandler input;

	Vector2 inputMoveDirection;

	float moveSpeed;
	float dashSpeed;

	bool balls = false;
};
