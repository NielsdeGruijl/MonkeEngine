#pragma once

// Pawns are dynamic GameObjects that can move

#include "GameObject.h"
#include "CharacterController.h"
#include "InputHandler.h"

class Pawn : public GameObject
{
public:
	Pawn(std::string objectId, std::string fileName, int pixelsPerUnit);
	~Pawn();

	void Update() override;


protected:
	CharacterController controller;
	InputHandler input;


private:
	Vector2 pawnPosition;
};