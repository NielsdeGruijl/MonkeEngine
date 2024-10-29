#include "Scene.h"

Scene::Scene() 
{
	InitializeObjectsInScene();
}

Scene::~Scene()
{
}

void Scene::RenderScene(sf::RenderWindow* renderWindow)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(renderWindow);
	}
}

void Scene::UpdateScene()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

void Scene::InitializeObjectsInScene() 
{
}


void Scene::AddObject(Object& object)
{
	objects.push_back(&object);
}

Object* Scene::FindObject(std::string objectId) const
{
	for (size_t i = objects.size(); i > 0; i--)
	{
		if (objects[i - 1]->GetID() != objectId) 
			continue;

		return objects[i - 1];
	}

	std::cout << "Couldn't find object with id \"" << objectId << "\"\n";

	return nullptr;
}