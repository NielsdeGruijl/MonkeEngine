//
// Created by niels on 4/16/26.
//

#include "Projectile.h"

#include "../Framework/Components/SpriteRenderer.h"

Projectile::Projectile(Scene *pScene, std::string pName, std::weak_ptr<GameObject> pTarget)
    : GameObject(pScene, pName), target(pTarget)
{
    rigidbody = AddComponent<RigidBody>(this);
    rigidbody->gravity = 0;

    AddComponent<SpriteRenderer>(this, "Purple.png", 160);
    SetScale(0.25f);

    moveSpeed = 30;
}

Projectile::~Projectile()
{
}

void Projectile::Start()
{
    GameObject::Start();

    if (target.expired())
        return;

    auto targetObject = target.lock();

    Vector2 velocity = (targetObject->position - position).Normalized();
    velocity *= moveSpeed;

    rigidbody->AddForce(velocity, RigidBody::instant);
}

void Projectile::OnCollisionEnter(std::weak_ptr<AABBCollider> pOtherCollider)
{
    GameObject::OnCollisionEnter(pOtherCollider);

    Destroy();
}
