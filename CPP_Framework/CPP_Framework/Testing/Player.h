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
	void Update() override;

	void SetActionMap(InputActionMap* pMap);

	std::shared_ptr<RigidBody> rigidBody;

protected:
	void OnCollisionEnter(GameObject* pObject) override;
	void OnCollisionStay(GameObject* pObject) override;
	void OnCollisionExit(GameObject* pObject) override;

private:
	InputActionMap defaultInputActionMap;
	InputHandler input;

	Vector2 inputMoveDirection;

	float moveSpeed;
	float dashSpeed;

	bool balls = false;
};
