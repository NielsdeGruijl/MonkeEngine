#include "Scene.h"
#include "../Math/Timer.h"

Scene::Scene() 
{
	isLoaded = false;
}

Scene::~Scene()
{
}

void Scene::UpdateScene()
{
	if (!isLoaded)
		return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}

	//collisionChecker.CheckCollisions();
}

void Scene::CollsionUpdate()
{
	if (!isLoaded)
		return;

	collisionChecker.CheckCollisions();
}

void Scene::RenderScene(sf::RenderWindow* renderWindow)
{
	if (!isLoaded)
		return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(renderWindow);
	}
}


void Scene::OnLoad()
{
	Timer timer;
	for (Object* object : objects)
	{
		object->OnLoad();

		RegisterCollider(object);
	}

	isLoaded = true;
}

void Scene::RegisterCollider(Object* object)
{
	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr <AABBCollider> collider;

	if(object->TryGetComponent(rigidBody))
		collisionChecker.AddRigidBody(rigidBody);
	else if (object->TryGetComponent(collider))
		collisionChecker.AddCollider(collider);
}

void Scene::AddObject(Object* object)
{
	objects.push_back(object);
}

Object* Scene::FindObjectByName(std::string objectId) const
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