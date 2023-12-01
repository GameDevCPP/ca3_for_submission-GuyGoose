
#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include <LevelSystem.h>
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

// Constructor for the bullet component.
BulletComponent::BulletComponent(Entity* p) : Component(p) {}

// Update the bullet.
void BulletComponent::update(double dt) {

}

// Render the bullet.
void BulletComponent::render() {}
