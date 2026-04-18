//
// Created by niels on 4/16/26.
//

#include "ShootingCollisionScene.h"

#include "Projectile.h"

ShootingCollisionScene::ShootingCollisionScene()
{
    target = std::make_shared<Enemy>(this, "Target");
    target->SetPosition(Vector2(960-50, 540+35));
    //AddObject(target);

    bulletDelayClock.restart();
    bulletDelay = 0.1f;

    bulletSpawnPositions.emplace_back(960, 0);
    bulletSpawnPositions.emplace_back(960, 1080);
    bulletSpawnPositions.emplace_back(0, 540);
    bulletSpawnPositions.emplace_back(1920, 540);
}

ShootingCollisionScene::~ShootingCollisionScene()
{
    std::cout << totalBullets << std::endl;
}

void ShootingCollisionScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    if (clock.getElapsedTime().asSeconds() > 10)
        canSpawn = false;

    Vector2 targetPosition;
    if (bulletDelayClock.getElapsedTime().asSeconds() > bulletDelay && canSpawn)
    {
        targetPosition = Vector2(std::rand() % 640, std::rand() % 480);
        targetPosition += Vector2(640, 300);

        Vector2 closestPosition;
        float closestDistance = 999999999;
        for (Vector2 spawnPosition : bulletSpawnPositions)
        {
            float currentDistance = (targetPosition - spawnPosition).GetLength();
            if (currentDistance < closestDistance)
            {
                closestDistance = currentDistance;
                closestPosition = spawnPosition;
            }
        }

        std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(this, "Projectile");
        projectile->SetPosition(closestPosition);
        projectile->Fire(targetPosition);
        AddObject(projectile);

        totalBullets++;

        bulletDelayClock.restart();
    }
}
