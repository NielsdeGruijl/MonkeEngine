#pragma once

// Scenes are the Objects that contain a level and all its GameObjects

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Objects/Pawn.h"
#include "../Collisions/CollisionChecker.h"

class Scene
{
public:
	Scene();
	~Scene();
	 
	virtual void RenderScene(sf::RenderWindow* renderWindow);
	virtual void UpdateScene();

	virtual void OnLoad();

	void AddObject(Object* object);
	Object* FindObjectByName(std::string objectId) const;

protected:
	std::vector<Object*> objects;
	std::vector<Pawn*> pawns;
	CollisionChecker collisionChecker;

	bool isLoaded;
};