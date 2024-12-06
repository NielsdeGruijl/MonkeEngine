#include "SceneManager.h"

SceneManager::SceneManager()
	: currentScene(nullptr)
{
}

SceneManager::SceneManager(std::string pSceneName, Scene* pDefaultScene)
	: currentScene(pDefaultScene)
{
	AddScene(pSceneName, pDefaultScene);
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

Scene* SceneManager::GetScene(std::string pSceneName)
{
	if (scenes.find(pSceneName) != scenes.end())
		return scenes.at(pSceneName);
	else
	{
		std::cout << "Scene with name \"" << pSceneName << "\" doesn't exist.\n";
		return nullptr;
	}
}

void SceneManager::AddScene(std::string pSceneName, Scene* pScene)
{
	if (scenes.find(pSceneName) != scenes.end())
	{
		std::cout << "Scene with name \"" << pSceneName << "\" already exists.\n";
		return;
	}

	std::cout << "Scene with name \"" << pSceneName << "\" has been added!\n";

	// If there are no scenes yet, load this scene.
	if (scenes.size() <= 0)
		LoadScene(pScene);
	
	scenes[pSceneName] = pScene;
}

void SceneManager::LoadScene(Scene* pScene)
{
	pScene->Load();
	currentScene = pScene;
}

void SceneManager::LoadScene(std::string pSceneName)
{
	LoadScene(GetScene(pSceneName));
}