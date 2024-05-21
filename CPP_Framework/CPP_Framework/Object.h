
// Object is the base class that every GameObject derives from.

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector2.h"

class Scene;

class Object
{
private:
	const std::string ID;

protected:
	Scene* scene;
	Vector2 position;
	Vector2 radius;

public:
	Object(std::string ID);
	~Object();

	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* widnow) = 0;
	void SetScene(Scene* scene);

	std::string GetID();

	virtual void SetPosition(const Vector2 pos);
	Vector2 GetPosition() const;
	Vector2 GetRadius() const;
};