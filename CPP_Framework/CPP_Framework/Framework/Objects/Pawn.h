#pragma once

// Pawns are dynamic GameObjects that can move

#include "../Components/CharacterController.h"
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	Pawn(std::string objectId, std::string fileName, int pixelsPerUnit);
	~Pawn();

	void Update() override;


protected:
	CharacterController controller;

private:
	Vector2 pawnPosition;
};