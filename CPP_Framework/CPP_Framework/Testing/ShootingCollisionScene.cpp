//
// Created by niels on 4/16/26.
//

#include "ShootingCollisionScene.h"

#include "Projectile.h"

ShootingCollisionScene::ShootingCollisionScene()
{
    target = std::make_shared<Enemy>(this, "Target");
    target->SetPosition(Vector2(960, 540));
    AddObject(target);

    bulletDelayClock.restart();
    bulletDelay = 1;
}

ShootingCollisionScene::~ShootingCollisionScene()
{
}

void ShootingCollisionScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    if (bulletDelayClock.getElapsedTime().asSeconds() > bulletDelay)
    {
        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(this, "Projectile", target);
        AddObject(projectile);

        bulletDelayClock.restart();
    }
}
