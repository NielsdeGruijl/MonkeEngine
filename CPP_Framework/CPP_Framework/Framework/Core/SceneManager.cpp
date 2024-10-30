#include "SceneManager.h"

SceneManager::SceneManager()
	: currentScene(nullptr)
{
}

SceneManager::SceneManager(std::string sceneName, Scene* defaultScene)
	: currentScene(defaultScene)
{
	AddScene(sceneName, defaultScene);
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::GetCurrentScene()
{
	if (currentScene == nullptr)
		std::cout << "currentScene cannot be null.\n";

	return currentScene;
}

Scene* SceneManager::GetScene(std::string sceneName)
{
	if (scenes.find(sceneName) != scenes.end())
		return scenes.at(sceneName);
	else
	{
		std::cout << "Scene with name \"" << sceneName << "\" doesn't exist.\n";
		return nullptr;
	}
}

void SceneManager::AddScene(std::string sceneName, Scene* scene)
{
	if (scenes.find(sceneName) != scenes.end())
	{
		std::cout << "Scene with name \"" << sceneName << "\" already exists.\n";
		return;
	}

	std::cout << "Scene with name \"" << sceneName << "\" has been added!\n";

	if (scenes.size() < 1)
		currentScene = scene;
	
	scenes[sceneName] = scene;
}

void SceneManager::SwitchScene(std::string sceneName)
{
	currentScene = GetScene(sceneName);
}