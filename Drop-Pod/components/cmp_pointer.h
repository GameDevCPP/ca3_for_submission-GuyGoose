#pragma once

#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

class PointerComponent : public Component {
protected:
    double fireTime = 0.0f;

public:
    PointerComponent() = delete;

    explicit PointerComponent(Entity* p);

    void update(double dt) override;

    // Implement the render method
    void render() override;

    // Get rotation
    float getRotation() const;

    ~PointerComponent() override = default;
};