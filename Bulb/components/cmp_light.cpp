
#include "cmp_light.h"
#include "system_renderer.h"
#include "system_physics.h"
#include "cmp_physics.h"
#include "ecm.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../components/cmp_sprite.h"
#include "cmp_player_physics.h"
#include <LevelSystem.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <utility>

using namespace std;
using namespace sf;

// Constructor for the light component.
LightComponent::LightComponent(Entity* p, const sf::Vector2f& size, shared_ptr<Entity> player, int lightNum) : PhysicsComponent(p, true, size)
{
    // Set the size of the light.
    _size = b2Vec2(size.x, size.y);
    // Set the player.
    _player = std::move(player);
    // Set the light number.
    _lightNum = lightNum;

    // Add a shape component to the light. This will be the light's sprite. A yellow slightly transparent circle.
    auto s = _parent->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(_size.x);
    // Set Color to #e5dacd
    s->getShape().setFillColor(Color(229, 218, 205, 100));
    s->getShape().setOrigin(Vector2f(_size.x, _size.y));
    // Set shape to have no collision.
    //s->getShape().setOutlineThickness(0);
    // Set the box2d body of the light to have no collision.
    _body->GetFixtureList()->SetSensor(true);

}

// Set Position
void LightComponent::setPosition(const sf::Vector2f& pos) {
    _parent->setPosition(pos);
}

void LightComponent::update(double dt) {
    // Increase and decrease the size of the light by 10% over 2 seconds.

    // If the light is increasing in size.
    if (increase) {
        // Increase the size of the light by 10%.
        currentSize = currentSize * 1.0002;
        // If the light is now bigger than 200.
        if (currentSize > 1.05) {
            // Set the light to decrease in size.
            increase = false;
        }
    }

    // If the light is decreasing in size.
    if (!increase) {
        // Decrease the size of the light by 10%.
        currentSize = currentSize * 0.9998;
        // If the light is now smaller than 100.
        if (currentSize < 0.95) {
            // Set the light to increase in size.
            increase = true;
        }
    }

    // Get the shape component of the light and set the size of the light to the current size.
    auto s = _parent->getComponent<ShapeComponent>();
    s->setScale(Vector2f(currentSize, currentSize));
    // Print the scale of the light.
    // cout << s->getScale() << endl;

    // If the player is colliding with the light. Check if the players _lights vector is empty, if it is, add lightnumber to the vector. else, check if lightnumber is in vector, if so remove it.
    if (isColliding(_player) && _player->getComponent<PlayerPhysicsComponent>()->getLights().empty()) {
        _player->getComponent<PlayerPhysicsComponent>()->addLight(_lightNum);
        // Debug print the lights vector.
        cout << "Lights: " << _player->getComponent<PlayerPhysicsComponent>()->getLights() << endl;
    }
    else if (!isColliding(_player) && !_player->getComponent<PlayerPhysicsComponent>()->getLights().empty()) {
        _player->getComponent<PlayerPhysicsComponent>()->removeLight(_lightNum);
        // Debug print the lights vector.
        cout << "Lights: " << _player->getComponent<PlayerPhysicsComponent>()->getLights() << endl;
    }

    // print player position
    //cout << _player->getPosition().x << " " << _player->getPosition().y << endl;
}

void LightComponent::render() {
}

bool LightComponent::isColliding(shared_ptr<Entity> e){
// Get the position of the player.
    auto playerPos = e->getPosition();
    // Get the position of the light.
    auto lightPos = _parent->getPosition();
    // Get the distance between the player and the light.
    auto distance = sqrt(pow(playerPos.x - lightPos.x, 2) + pow(playerPos.y - lightPos.y, 2));
    // If the distance is less than the size of the light, return true.
    if (distance < _size.x) {
        return true;
    }
    // If the distance is greater than the size of the light, return false.
    else {
        return false;
    }
}









