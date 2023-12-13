#include "cmp_player_anim.h"
#include "cmp_light.h"
#include "cmp_player_physics.h"
#include "system_resources.h"
#include "SFML/Window/Keyboard.hpp"

using namespace std;
using namespace sf;

PlayerAnimatorComponent::PlayerAnimatorComponent(Entity* p) : Component(p) {
    sprite = _parent->getComponent<SpriteComponent>();
    anim = _parent->getComponent<AnimationComponent>();
    playerRect = IntRect(0,0,32,32);
}

void PlayerAnimatorComponent::update(double dt) {


    // If A is pressed play run animation, if D is pressed play run animation (flipped), else play idle animation
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        // Flip the sprite
        sprite->getSprite().setScale(-1.f,1.f);
        anim->setAnimation(4,0.1,Resources::get<Texture>("run.png"),playerRect);
    }
    else if (Keyboard::isKeyPressed(Keyboard::D)) {
        // Flip the sprite
        sprite->getSprite().setScale(1.f,1.f);
        anim->setAnimation(4,0.1,Resources::get<Texture>("run.png"),playerRect);
    }
    else {
        anim->setAnimation(4,0.1,Resources::get<Texture>("idle.png"),playerRect);
    }
}

void PlayerAnimatorComponent::render() {
}
