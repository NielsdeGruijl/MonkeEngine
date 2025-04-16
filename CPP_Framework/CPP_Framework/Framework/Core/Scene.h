#pragma once

// Scenes are the Objects that contain a level and all its GameObjects

#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneRenderer.h"
#include "../Objects/GameObject.h"
#include "../Collisions/CollisionChecker.h"

class Scene
{
public:
	Scene();
	~Scene();
	 
	virtual void UpdateScene();
	virtual void CollisionUpdate();
	virtual void RenderScene(sf::RenderWindow* renderWindow);

	virtual void Load();

	void CleanUpObjects();

	void RegisterCollider(GameObject* object);
	void RegisterSprite(GameObject* object);

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);
	GameObject* FindObjectByName(std::string objectId) const;

protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> objectsToDelete;

	CollisionChecker collisionChecker;
	SceneRenderer sceneRenderer;

	bool isLoaded;
};