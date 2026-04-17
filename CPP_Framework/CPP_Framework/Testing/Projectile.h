//
// Created by niels on 4/16/26.
//

#ifndef MYPROJECT_PROJECTILE_H
#define MYPROJECT_PROJECTILE_H
#include "../Framework/Objects/GameObject.h"


class Projectile : public GameObject
{
public:
    Projectile(Scene* pScene, std::string pName);
    ~Projectile();

    void Fire(Vector2 targetPosition);

private:
    std::shared_ptr<RigidBody> rigidbody;

    float moveSpeed = 0;
};


#endif //MYPROJECT_PROJECTILE_H