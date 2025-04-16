#include "Object.h"

#include "../Collisions/AABBCollider.h"
#include "../Core/Scene.h"

extern const int unitSize;

Object::Object(Scene* pScene, std::string ID)
	: scene(pScene), objectId(ID)
{
	size = Vector2(unitSize, unitSize);
}

Object::~Object()
{
	for (std::shared_ptr<Component> component : components)
	{
		component.reset();
	}
}

void Object::OnLoad()
{
	for (std::shared_ptr<Component> component : components)
	{
		component->OnLoad();

		if (typeid(*(component)) == typeid(AABBCollider))
		{
			std::shared_ptr<AABBCollider> tCol = std::static_pointer_cast<AABBCollider>(component);

			tCol->collisionEnterEvent.Subscribe([this]() {this->OnCollisionEnter(); });
			tCol->collisionStayEvent.Subscribe([this]() {this->OnCollisionStay(); });
			tCol->collisionExitEvent.Subscribe([this]() {this->OnCollisionExit(); });
			tCol->paramCollisionEnterEvent.AddListener([this](Object* object) {this->OnParamCollisionEnter(object); });
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

void Object::Destroy()
{
	scene->RemoveObject(this);
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

void Object::OnParamCollisionEnter(Object* object)
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