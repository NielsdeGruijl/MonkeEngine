//
// Created by niels on 4/16/26.
//

#ifndef MYPROJECT_SHOOTINGCOLLISIONSCENE_H
#define MYPROJECT_SHOOTINGCOLLISIONSCENE_H
#include "Enemy.h"
#include "../Framework/Core/Scene.h"


class ShootingCollisionScene : public Scene
{
public:
    ShootingCollisionScene();
    ~ShootingCollisionScene();

    void Update(float deltaTime) override;

private:
    std::shared_ptr<Enemy> target;

    sf::Clock bulletDelayClock;

    sf::Clock clock;

    bool canSpawn = true;;

    std::vector<Vector2> bulletSpawnPositions;

    float bulletDelay = 0;

    float totalBullets = 0;
};


#endif //MYPROJECT_SHOOTINGCOLLISIONSCENE_H