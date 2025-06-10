
// GameObject is the base class that every GameObject derives from.

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"
#include "../Math/Timer.h"

#include "../Components/Component.h"
#include "../Components/RigidBody.h"


class Scene;
class AABBCollider;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	Vector2 origin;
	Vector2 previousPosition;
	Vector2 position;
	Vector2 scale;

public:
	GameObject(Scene* pScene, std::string ID);
	~GameObject();

	virtual void OnLoad();
	virtual void Start();

	virtual void FixedUpdate();
	virtual void Update();

	virtual void Destroy();

	void SetScale(const Vector2 pScale);
	void SetScale(const float pScale);
	void SetPosition(const Vector2 pPosition);
	void SetOrigin(const Vector2 pOrigin);

	void SetCollisionEvents();

	std::string GetID() const;
	Vector2 GetSize();

public:
	template <typename T, typename... ConstructorArgs>
	std::shared_ptr<T> AddComponent(ConstructorArgs&&... pConstructorArgs)
	{
		std::shared_ptr<T> componentPointer = std::make_shared<T>(std::forward<ConstructorArgs>(pConstructorArgs)...);

		//if (std::shared_ptr<AABBCollider> collider = std::dynamic_pointer_cast<AABBCollider>(componentPointer))
		//	physicsComponents.push_back(collider);
		std::shared_ptr<RigidBody> rigidBody = std::dynamic_pointer_cast<RigidBody>(componentPointer);
		std::shared_ptr<AABBCollider> collider = std::dynamic_pointer_cast<AABBCollider>(componentPointer);

		if(rigidBody || collider)
			physicsComponents.push_back(componentPointer);
		else
			components.push_back(componentPointer);
		
		return componentPointer;
	}

	template <typename T>
	bool TryGetComponent(std::shared_ptr<T>& pOut)
	{
		for (std::shared_ptr<Component>& component : components)
		{
			if (pOut = std::dynamic_pointer_cast<T>(component))
				return true;
		}
		for (std::shared_ptr<Component>& component : physicsComponents)
		{
			if (pOut = std::dynamic_pointer_cast<T>(component))
				return true;
		}
		return false;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (std::shared_ptr<Component> component : components)
		{
			if (std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component))
				return castedComponent;
		}
		for (std::shared_ptr<Component> component : physicsComponents)
		{
			if (std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component))
				return castedComponent;
		}
		return nullptr;
	}

	template <typename T>
	std::vector<std::shared_ptr<T>> GetComponents()
	{
		std::vector<std::shared_ptr<T>> tComponents;

		for (size_t i = 0; i < components.size(); i++)
		{
			if (typeid(*(components[i])) == typeid(T))
			{
				tComponents.push_back(std::static_pointer_cast<T>(components[i]));
			}
		}

		return tComponents;
	}

protected:
	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> physicsComponents;

	Scene* scene;

protected:
	virtual void OnCollisionEnter(GameObject* object);
	virtual void OnCollisionStay(GameObject* object);
	virtual void OnCollisionExit(GameObject* object);

private:
	const std::string objectId;
	Vector2 size;
};