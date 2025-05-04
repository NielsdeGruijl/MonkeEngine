#include "GameObject.h"

#include "../Collisions/AABBCollider.h"
#include "../Core/Scene.h"

extern const int unitSize;

GameObject::GameObject(Scene* pScene, std::string ID)
	: scene(pScene), objectId(ID), scale(Vector2(1, 1))
{
	size = Vector2(unitSize, unitSize);
	SetOrigin(Vector2(0.5f, 0.5f));
}

GameObject::~GameObject()
{
	components.clear();
}

void GameObject::OnLoad()
{
	for (std::shared_ptr<Component> component : components)
	{
		component->OnLoad();

		if (typeid(*(component)) == typeid(AABBCollider))
		{
			std::shared_ptr<AABBCollider> tCol = std::static_pointer_cast<AABBCollider>(component);

			tCol->collisionEnterEvent.AddListener([this](GameObject* pObject) {this->OnCollisionEnter(pObject); });
			tCol->collisionStayEvent.AddListener([this](GameObject* pObject) {this->OnCollisionStay(pObject); });
			tCol->collisionExitEvent.AddListener([this](GameObject* pObject) {this->OnCollisionExit(pObject); });
		}
	}
}

void GameObject::Start()
{
}

void GameObject::Update()
{
	for (std::shared_ptr<Component> component : components)
	{
		if (!component->IsActive())
			return;

		component->Update();
	}
}

void GameObject::Destroy()
{
	scene->RemoveObject(shared_from_this());
}

void GameObject::OnCollisionStay(GameObject* object)
{
}

void GameObject::OnCollisionExit(GameObject* object)
{
	std::cout << "exit\n";
}

void GameObject::OnCollisionEnter(GameObject* object)
{
	std::cout << "enter\n";

}

void GameObject::SetScale(const Vector2 pScale)
{
	scale = pScale;
	size = Vector2(unitSize * scale.x, unitSize * scale.y);

	std::shared_ptr<SpriteRenderer> sprite;
	if (TryGetComponent<SpriteRenderer>(sprite))
	{
		sprite->SetScale(scale);
	}
}

void GameObject::SetScale(const float pScale)
{
	SetScale(Vector2(pScale, pScale));
}

void GameObject::SetPosition(const Vector2 pPosition)
{
	position = pPosition;
}

void GameObject::SetOrigin(const Vector2 pOrigin)
{
	origin = size * pOrigin;
}

void GameObject::SetCollisionEvents()
{
}

std::string GameObject::GetID() const
{
	return objectId;
}

Vector2 GameObject::GetSize()
{
	return size;
}