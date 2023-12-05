
#include "cmp_light.h"
#include "system_renderer.h"
#include "system_physics.h"
#include "cmp_physics.h"
#include "ecm.h"
// Circle shape
#include <SFML/Graphics/CircleShape.hpp>
#include "../components/cmp_sprite.h"
#include "cmp_player_physics.h"
#include <LevelSystem.h>
#include <iostream>
#include <math.h>
#include <thread>

using namespace std;
using namespace sf;

// Constructor for the light component.
LightComponent::LightComponent(Entity* p, const sf::Vector2f& size, shared_ptr<Entity> player) : PhysicsComponent(p, true, size)
{
    // Set the size of the light.
    _size = b2Vec2(size.x, size.y);

    // Add a shape component to the light. This will be the light's sprite. A yellow slightly transparent circle.
    auto s = _parent->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(_size.x);
    s->getShape().setFillColor(Color(255, 255, 0, 100));
    s->getShape().setOrigin(Vector2f(_size.x, _size.y));

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
    cout << s->getScale() << endl;

    
}

void LightComponent::render() {
}

bool LightComponent::isColliding(shared_ptr<Entity> e){
    // Get the position of the light.
    Vector2f lightPos = _parent->getPosition();
    // Get the position of the entity.
    Vector2f entityPos = e->getPosition();
    // Get the distance between the light and the entity.
    float distance = sqrt(pow((lightPos.x - entityPos.x), 2) + pow((lightPos.y - entityPos.y), 2));
    // Get the size of the light.
    float lightSize = _size.x;
    // Get the size of the entity.
    auto entitySize = e->getComponent<ShapeComponent>()->getShape().getLocalBounds().width;
    // If the distance between the light and the entity is less than the size of the light plus the size of the entity.
    if (distance < lightSize + entitySize) {
        // Return true.
        return true;
    }
    // Otherwise return false.
    return false;
}





