#pragma once

// Scenes are the Objects that contain a level and all its GameObjects

#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneRenderer.h"
#include "../Objects/GameObject.h"
#include "../Collisions/CollisionChecker.h"
#include "../Collisions/BruteForce.h"
#include "../Collisions/SweepAndPrune.h"
#include "../Collisions/TwoDimensionalSAP.h"

class Scene
{
public:
	Scene();
	~Scene();
	 
	virtual void FixedUpdate();
	virtual void Update();
	virtual void RenderScene(sf::RenderWindow* renderWindow);

	virtual void Load();

	void CleanUpObjects();

	void RegisterCollider(GameObject* object);
	void RegisterSprite(GameObject* object);

	void AddObject(std::shared_ptr<GameObject> gameObject);
	void RemoveObject(std::shared_ptr<GameObject> gameObject);
	GameObject* FindObjectByName(std::string objectId) const;

protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> objectsToDelete;

	std::vector<std::shared_ptr<GameObject>> sharedObjects;
	std::vector<std::shared_ptr<GameObject>> sharedObjectsToDelete;

	BruteForce bruteForce;
	SweepAndPrune sweepAndPrune;
	TwoDimensionalSAP twoDimensionalSAP;
	CollisionChecker collisionChecker;
	SceneRenderer sceneRenderer;

	bool isLoaded;
};