
// Object is the base class that every GameObject derives from.

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"

#include "../Components/Component.h"

class Scene;

class Object
{
public:
	Vector2 origin;
	Vector2 position;
	Vector2 scale;

public:
	Object(std::string ID);
	~Object();

	virtual void OnLoad();
	virtual void Start();

	virtual void Update();
	virtual void Render(sf::RenderWindow* renderWindow) = 0;


	void SetScale(const Vector2 pScale);
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

		components.push_back(componentPointer);

		return componentPointer;
	}

	template <typename T>
	bool TryGetComponent(std::shared_ptr<T>& pOut)
	{
		for (std::shared_ptr<Component>& component : components)
		{
			if (typeid(*(component)) == typeid(T))
			{
				pOut = std::static_pointer_cast<T>(component);
				return true;
			}
		}
		return false;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (typeid(*(components[i])) == typeid(T))
			{
				return std::static_pointer_cast<T>(components[i]);
			}
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

protected:
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

private:
	const std::string objectId;
	Vector2 size;
};