#include "Object.h"

#include "../Collisions/AABBCollider.h"

extern const int unitSize;

Object::Object(std::string ID) 
	: objectId(ID)
{
	size = Vector2(unitSize, unitSize);
}

Object::~Object()
{
}

void Object::OnLoad()
{
	for (std::shared_ptr<Component> component : components)
	{
		component->OnLoad();

		if (std::shared_ptr<AABBCollider> tCollider = std::dynamic_pointer_cast<AABBCollider>(component))
		{
			tCollider->collisionEnterEvent.Subscribe([this]() {this->OnCollisionEnter(); });
		}
	}
}

void Object::Start()
{
}

void Object::Update()
{
	for (std::shared_ptr<Component> component : components)
	{
		if (!component->IsActive())
			return;

		component->Update();
	}
}

void Object::OnCollisionEnter()
{
}

void Object::OnCollisionStay()
{
}

void Object::OnCollisionExit()
{
}

void Object::SetScale(const Vector2 pScale)
{
	scale = pScale;
	size = Vector2(unitSize * scale.x, unitSize * scale.y);
}

void Object::SetPosition(const Vector2 pPosition)
{
	position = pPosition;
}

void Object::SetOrigin(const Vector2 pOrigin)
{
	origin = size * pOrigin;
}

void Object::SetCollisionEvents()
{
}

std::string Object::GetID() const
{
	return objectId;
}

Vector2 Object::GetSize()
{
	return size;
}