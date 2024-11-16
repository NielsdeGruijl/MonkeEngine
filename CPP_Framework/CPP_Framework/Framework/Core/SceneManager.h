#pragma once

#include <unordered_map>

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	SceneManager(std::string pSceneName, Scene* pDefaultScene);
	~SceneManager();

	Scene* GetCurrentScene();
	Scene* GetScene(std::string pSceneName);

	void AddScene(std::string pSceneName, Scene* pScene);

	void LoadScene(Scene* pScene);
	void LoadScene(std::string pSceneName);

private:
	std::unordered_map<std::string, Scene*> scenes;
	Scene* currentScene;
};