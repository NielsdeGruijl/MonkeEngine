//
// Created by niels on 4/16/26.
//

#ifndef MYPROJECT_PROJECTILE_H
#define MYPROJECT_PROJECTILE_H
#include "../Framework/Objects/GameObject.h"


class Projectile : public GameObject
{
public:
    Projectile(Scene* pScene, std::string pName, std::weak_ptr<GameObject> pTarget);
    ~Projectile();

    void Start() override;

protected:
    void OnCollisionEnter(GameObject *object) override;

private:
    std::shared_ptr<RigidBody> rigidbody;
    std::weak_ptr<GameObject> target;

    float moveSpeed = 0;
};


#endif //MYPROJECT_PROJECTILE_H