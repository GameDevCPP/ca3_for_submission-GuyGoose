// A white rectangle that rotates around the player. This is the base for the player's weapon.
// Rotates to point at the mouse.

#include "cmp_pointer.h"
#include "cmp_bullet.h"
#include <LevelSystem.h>
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <math.h>
#include <thread>

using namespace std;
using namespace sf;

// Constructor for the pointerArrow component.
PointerComponent::PointerComponent(Entity* p) : Component(p) {}


void PointerComponent::update(double dt) {

    // Depending on the mouse position, rotate the pointerArrow to point at the mouse.
    // Get the mouse position.
    Vector2i mousePos = Mouse::getPosition(Engine::GetWindow());
    // Get the player position.
    Vector2f playerPos = _parent->getPosition();
    // Get the angle between the mouse and the player.
    float angle = atan2(mousePos.y - playerPos.y, mousePos.x - playerPos.x);
    // Convert the angle to degrees.
    angle = angle * 180 / 3.14159265;

    // Set the rotation of the pointerArrow to the angle.
    _parent->setRotation(angle);
    _parent->getComponent<SpriteComponent>()->getSprite().setRotation(angle);
    //cout<<angle<<endl;

    // If the player presses the left mouse button, fire the pointerArrow.
    fireTime -= dt;

    if (fireTime <= 0 && Mouse::isButtonPressed(Mouse::Left)) {
        for (int i = 0; i < 5; ++i) {
            // Fire a bullet.
            _parent->GetCompatibleComponent<ShootingComponent>()[0]->Fire();
        }
        fireTime = 0.5f;
    }


    // Spin the pointerArrow. For testing purposes.
//    _parent->setRotation(_parent->getRotation() + 5);
}

// Get the rotation of the pointerArrow.
//float PointerComponent::getRotation() const {
//    return _parent->getRotation();
//}



void PointerComponent::render() {

}




