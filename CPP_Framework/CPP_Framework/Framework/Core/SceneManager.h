#pragma once

#include <unordered_map>

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	SceneManager(std::string sceneName, Scene* defaultScene);
	~SceneManager();

	Scene* GetCurrentScene();
	Scene* GetScene(std::string sceneName);

	void AddScene(std::string sceneName, Scene* scene);

	void SwitchScene(std::string sceneName);

private:
	std::unordered_map<std::string, Scene*> scenes;
	Scene* currentScene;
};