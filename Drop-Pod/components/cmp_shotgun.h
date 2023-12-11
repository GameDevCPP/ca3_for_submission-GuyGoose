#pragma once

#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

class ShotgunComponent : public Component {
protected:
    double fireTime = 0.0f;

public:
    ShotgunComponent() = delete;

    explicit ShotgunComponent(Entity* p);

    void update(double dt) override;

    // Implement the render method
    void render() override;

    // Get rotation
    float getRotation() const;

    ~ShotgunComponent() override = default;
};