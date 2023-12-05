// A white rectangle that rotates around the player. This is the base for the player's weapon.
// Rotates to point at the mouse.

#include "cmp_shotgun.h"
#include <LevelSystem.h>
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

// Constructor for the shotgun component.
ShotgunComponent::ShotgunComponent(Entity* p) : Component(p) {}


void ShotgunComponent::update(double dt) {

    // Depending on the mouse position, rotate the shotgun to point at the mouse.
    // Get the mouse position.
    Vector2i mousePos = Mouse::getPosition(Engine::GetWindow());
    // Get the player position.
    Vector2f playerPos = _parent->getPosition();
    // Get the angle between the mouse and the player.
    float angle = atan2(mousePos.y - playerPos.y, mousePos.x - playerPos.x);
    // Convert the angle to degrees.
    angle = angle * 180 / 3.14159265;

    // Set the rotation of the shotgun to the angle.
    _parent->setRotation(angle);
    _parent->getComponent<ShapeComponent>()->setRotation(angle);
    cout<<angle<<endl;


    // Spin the shotgun. For testing purposes.
//    _parent->setRotation(_parent->getRotation() + 5);
}

// Get the rotation of the shotgun.
//float ShotgunComponent::getRotation() const {
//    return _parent->getRotation();
//}



void ShotgunComponent::render() {

}




