#pragma once

// Include animation component
#include "cmp_player_anim.h"
#include "cmp_light.h"
#include "cmp_player_physics.h"

class PlayerAnimatorComponent : public Component {

protected:
    bool _flip = false;
    bool _moving = false;
public:
    PlayerAnimatorComponent() = delete;

    explicit PlayerAnimatorComponent(Entity* p);

    void update(double dt) override;

    void render() override;

    ~PlayerAnimatorComponent() override = default;
};