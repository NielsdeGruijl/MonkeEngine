#include "Scene.h"
#include "../Math/Timer.h"
#include "../../Asteroids/Bullet.h"

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

	for (size_t i = 0; i < sharedObjects.size(); i++)
	{
		sharedObjects[i]->Update();
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

	for (std::shared_ptr<GameObject> object : sharedObjects)
	{
		object->OnLoad();
		
		RegisterCollider(object.get());

		object->Start();
	}
}

void Scene::CleanUpObjects()
{
	for (std::shared_ptr<GameObject> gameObject : sharedObjectsToDelete)
	{
		auto it = std::find(sharedObjects.begin(), sharedObjects.end(), gameObject);
		sharedObjects.erase(it);
	}

	sharedObjectsToDelete.clear();
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

void Scene::AddObject(std::shared_ptr<GameObject> gameObject)
{
	sharedObjects.push_back(gameObject);

	RegisterSprite(gameObject.get());

	if (isLoaded)
	{
		gameObject->OnLoad();

		RegisterCollider(gameObject.get());

		gameObject->Start();
	}
}

void Scene::RemoveObject(std::shared_ptr<GameObject> gameObject)
{
	sharedObjectsToDelete.push_back(gameObject);
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