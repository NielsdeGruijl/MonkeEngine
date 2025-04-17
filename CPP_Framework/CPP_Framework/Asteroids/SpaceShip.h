#pragma once

#include "../Framework/Input/InputActionMap.h"
#include "../Framework/Input/InputHandler.h"

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Components/RigidBody.h"

class SpaceShip : public GameObject
{
public:
	SpaceShip(Scene* pScene, std::string pId);
	~SpaceShip();

	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<SpriteRenderer> sprite;

private:
	void OnLoad() override;
	void Start() override;
	void Update() override;
	
	void OnCollisionEnter(GameObject* object) override;

	InputActionMap inputActionMap;
	InputHandler input;

	Vector2 velocity;

	float moveSpeed;

	float bulletSizeMultiplier;
};