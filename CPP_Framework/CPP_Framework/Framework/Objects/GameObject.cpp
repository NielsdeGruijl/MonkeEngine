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
	std::cout << "Destroying " << objectId << std::endl;

	components.clear();
}

void GameObject::OnLoad()
{
	for (std::shared_ptr<Component> component : components)
	{
		component->OnLoad();
	}

	for (std::shared_ptr<Component> component : physicsComponents)
	{
		component->OnLoad();

		if (typeid(*(component)) == typeid(AABBCollider))
		{
			std::shared_ptr<AABBCollider> tCol = std::static_pointer_cast<AABBCollider>(component);

			tCol->collisionEnterEvent.AddListener([this](std::weak_ptr<AABBCollider> pOtherCollider) {this->OnCollisionEnter(pOtherCollider); });
			tCol->collisionStayEvent.AddListener([this](std::weak_ptr<AABBCollider> pOtherCollider) {this->OnCollisionStay(pOtherCollider); });
			tCol->collisionExitEvent.AddListener([this](std::weak_ptr<AABBCollider> pOtherCollider) {this->OnCollisionExit(pOtherCollider); });
		}
	}
}

void GameObject::Start()
{
}

void GameObject::FixedUpdate(float fixedDeltaTime)
{
	previousPosition = position;

	for (std::shared_ptr<Component> component : physicsComponents)
	{
		if (!component->IsActive())
			continue;

		component->Update(fixedDeltaTime);
	}
}

void GameObject::Update(float deltaTime)
{
	for (std::shared_ptr<Component> component : components)
	{
		if (!component->IsActive())
			continue;

		component->Update(deltaTime);
	}
}

void GameObject::Destroy()
{
	scene->RemoveObject(shared_from_this());
}

void GameObject::OnCollisionStay(std::weak_ptr<AABBCollider> pOtherCollider)
{
}

void GameObject::OnCollisionExit(std::weak_ptr<AABBCollider> pOtherCollider)
{
}

void GameObject::OnCollisionEnter(std::weak_ptr<AABBCollider> pOtherCollider)
{

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