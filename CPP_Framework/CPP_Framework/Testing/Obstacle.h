#pragma once

#include "../Framework/Objects/GameObject.h"
#include "../Framework/Collisions/AABBCollider.h"

class Obstacle : public GameObject
{
public:
	Obstacle(std::string pID, std::string pFileName, int pPixelsPerUnit);
	~Obstacle();

	void Update() override;
};