#pragma once

// Include animation component
#include "cmp_player_anim.h"
#include "cmp_light.h"
#include "cmp_player_physics.h"

class PlayerAnimatorComponent : public Component {

protected:
    std::shared_ptr<SpriteComponent> sprite;
    std::shared_ptr<AnimationComponent> anim;
    sf::IntRect playerRect;
public:
    PlayerAnimatorComponent() = delete;

    explicit PlayerAnimatorComponent(Entity* p);

    void update(double dt) override;

    void render() override;

    ~PlayerAnimatorComponent() override = default;
};