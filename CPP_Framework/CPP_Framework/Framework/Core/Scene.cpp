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

	collisionChecker.CheckCollisions();
}

void Scene::CollisionUpdate()
{
	if (!isLoaded)
		return;
}

void Scene::RenderScene(sf::RenderWindow* renderWindow)
{
	if (!isLoaded)
		return;

	sceneRenderer.RenderSprites(renderWindow);
}

void Scene::Load()
{
	isLoaded = true;

	for (GameObject* object : objects)
	{
		object->OnLoad();
		
		RegisterCollider(object);

		object->Start();
	}
}

void Scene::CleanUpObjects()
{
	for (GameObject* object : objectsToDelete)
	{
		auto it = std::find(objects.begin(), objects.end(), object);
		objects.erase(it);
		
		delete object;
	}

	objectsToDelete.clear();
}

void Scene::RegisterCollider(GameObject* object)
{
	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<AABBCollider> collider;

	if(object->TryGetComponent(rigidBody))
		collisionChecker.AddRigidBody(rigidBody);
	else if (object->TryGetComponent(collider))
		collisionChecker.AddCollider(collider);
}

void Scene::RegisterSprite(GameObject* pObject)
{
	std::shared_ptr<SpriteRenderer> sprite;
	if (pObject->TryGetComponent<SpriteRenderer>(sprite))
	{
		sceneRenderer.AddSprite(sprite);
	}
}

void Scene::AddObject(GameObject* pObject)
{
	objects.push_back(pObject);

	RegisterSprite(pObject);

	if (isLoaded)
	{
		pObject->OnLoad();

		RegisterCollider(pObject);

		pObject->Start();
	}
}

void Scene::RemoveObject(GameObject* pObject)
{
	objectsToDelete.push_back(pObject);
}

GameObject* Scene::FindObjectByName(std::string objectId) const
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