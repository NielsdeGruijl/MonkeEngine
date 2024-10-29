#pragma once

// Scenes are the Objects that contain a level and all its GameObjects

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Objects/Pawn.h"

class Scene
{
public:
	Scene();
	~Scene();

	void RenderScene(sf::RenderWindow* renderWindow);
	void UpdateScene();

	virtual void InitializeObjectsInScene();
	void AddObject(Object& object);
	Object* FindObject(std::string objectId) const;

private:
	std::vector<Object*> objects;
};