
// Object is the base class that every GameObject derives from.

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Math/Vector2.h"

class Scene;

class Object
{
public:
	Vector2 position;
	Vector2 size;

public:
	Object(std::string ID);
	~Object();

	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow* renderWindow) = 0;
	
	std::string GetID() const;

protected:
	void SetPosition(const Vector2 pos);

private:
	const std::string objectId;
};