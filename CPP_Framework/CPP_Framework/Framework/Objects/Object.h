
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

	virtual void Update();
	virtual void Render(sf::RenderWindow* renderWindow) = 0;

	void SetScale(const Vector2 pScale);
	void SetPosition(const Vector2 pPosition);
	void SetOrigin(const Vector2 pOrigin);

	template <typename T, typename... ConstructorArgs>
	void AddComponent(ConstructorArgs&&... constructorArgs)
	{
		std::shared_ptr<T> componentPointer = std::make_shared<T>(std::forward<ConstructorArgs>(constructorArgs)...);

		std::shared_ptr<Component> tComponent = std::dynamic_pointer_cast<Component>(componentPointer);
		tComponent->SetObject(this);

		components.push_back(componentPointer);
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

	std::string GetID() const;
	Vector2 GetSize();

private:
	std::vector<std::shared_ptr<Component>> components;

	const std::string objectId;
	Vector2 size;
};