#pragma once

#include "cmp_physics.h"

class LightComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  float currentSize = 1;
  bool increase = true;
public:
    LightComponent() = delete;

    explicit LightComponent(Entity* p, const sf::Vector2f& size, shared_ptr<Entity> player);

    // Set Position
    void setPosition(const sf::Vector2f& pos);

    void update(double dt) override;

    void render() override;

    ~LightComponent() override = default;

    bool isColliding(std::shared_ptr<Entity> e);
};