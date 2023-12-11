
#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include "system_renderer.h"
#include <LevelSystem.h>
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

unsigned int bulletCount;
vector<Bullet> bullets(256);

float tempAngle;
shared_ptr<float> angleshot = make_shared<float>(tempAngle);

// Bullet Variables
bool isVisible = false;
float angle;
Vector2f mousePos;

auto tempSprite = Texture();
auto spriteTexture = make_shared<Texture>(tempSprite);

ShootingComponent::ShootingComponent(Entity* p) : Component(p) {
    Bullet::init();
    

}

void ShootingComponent::update(double dt) {
    Bullet::update(dt);
}

void ShootingComponent::render() {
    Bullet::render();
}

void ShootingComponent::Fire() {
    printf("Firing\n");

    Bullet::fire(_parent->getPosition());
}

Bullet::Bullet() {}

void Bullet::init() {
    printf("Bullet Init\n");
    spriteTexture = Resources::get<Texture>("bulletGlow.png");

    for (auto& b : bullets) {
        b.setPosition(Vector2f(-1000, -1000));
        b.setTexture(*spriteTexture);
        b.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
        b.setOrigin(Vector2f(spriteTexture->getSize().x * 0.5 - 15, spriteTexture->getSize().y * 0.5));
        b.setAngle(0.f, b);
        b.mousePos = Vector2f(0, 0);
        b.isVisible = false;
    }
    // Print the number of bullets.
    printf("Number of bullets: %d\n", bullets.size());

    printf("Bullet Init Complete\n");
}

void Bullet::setAngle(float a, Bullet &b) {
    // Add a tiny varience to the angle to better simulate a shotgun. Between +- 5 degrees.
    b.angle = a + ((rand() % 10) - 5) * 0.0174533;
}

void Bullet::update(const double dt) {
    for (auto& b: bullets) {
        b._update(dt);
    }
}

void Bullet::render() {
    for (auto& b : bullets) {
        if (b.isVisible) {
            Renderer::queue(&b);
        }
    }
}

void Bullet::fire(const Vector2f& pos) {
    RenderWindow& window = Engine::GetWindow();
    auto mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    bulletCount++;
    bulletCount = bulletCount % 256;
    bullets[bulletCount].setPosition(pos);
    bullets[bulletCount].isVisible = true;

    *angleshot = atan2(mousePos.y - bullets[bulletCount].getPosition().y, mousePos.x - bullets[bulletCount].getPosition().x);
    bullets[bulletCount].setAngle(*angleshot, bullets[bulletCount]);
}

void Bullet::_update(const double dt) {
    RenderWindow& window = Engine::GetWindow();
    const View view = window.getView();

    // Basic animation
//    if (getTextureRect().left == 0) {
//        setTextureRect(IntRect(Vector2i(32, 0), Vector2i(32, 32)));
//    }
//    else {
//        setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
//    }

    // If bullet is out of bounds. remove/return;
    if (getPosition().x < view.getCenter().x - 100 - view.getSize().x * 0.5 || getPosition().x > view.getCenter().x + 100 + view.getSize().x * 0.5
        || getPosition().y < view.getCenter().y - 100 - view.getSize().y * 0.5 || getPosition().y > view.getCenter().y + 100 + view.getSize().y * 0.5)
    {
        this->isVisible = false;
        return;
    }
    else {
        this->move(cos(this->angle) * 750.f * dt, 0);
        this->move(0, sin(this->angle) * 750.f * dt);
    }
}