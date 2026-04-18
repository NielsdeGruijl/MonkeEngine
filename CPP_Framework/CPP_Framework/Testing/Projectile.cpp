//
// Created by niels on 4/16/26.
//

#include "Projectile.h"

#include "../Framework/Components/SpriteRenderer.h"

Projectile::Projectile(Scene *pScene, std::string pName)
    : GameObject(pScene, pName)
{
    rigidbody = AddComponent<RigidBody>(this);
    rigidbody->gravity = 0;

    AddComponent<SpriteRenderer>(this, "AABBTest.png", 640);
    SetScale(0.5f);

    moveSpeed = 20;
}

Projectile::~Projectile()
{
}

void Projectile::Fire(Vector2 targetPosition)
{
    Vector2 velocity = (targetPosition - position).Normalized();
    velocity *= moveSpeed;

    rigidbody->AddForce(velocity, RigidBody::instant);
}
