#include "Scene.h"

Scene::Scene() 
{
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

	//collisionChecker.CheckCollisions();
}

void Scene::AddObject(Object* object)
{
	objects.push_back(object);

	if (Pawn* pawn = dynamic_cast<Pawn*>(object))
	{
		//if (std::shared_ptr<CharacterController> cotroller = pawn->GetComponent<CharacterController>())
		//	collisionChecker.AddCharacterController(cotroller);
		if (std::shared_ptr<AABBCollider> collider = pawn->GetComponent<AABBCollider>())
			collisionChecker.AddCollider(collider, true);
	}
	else
	{
		if (std::shared_ptr<AABBCollider> collider = object->GetComponent<AABBCollider>())
			collisionChecker.AddCollider(collider);
	}
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