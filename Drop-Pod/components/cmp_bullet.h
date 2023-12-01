#pragma once

#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

class BulletComponent : public Component {
protected:
    int bulletSpeed = 1000;

public:
    BulletComponent() = delete;

    explicit BulletComponent(Entity* p);

    void update(double dt) override;

    // Implement the render method
    void render() override;

    ~BulletComponent() override = default;
};
