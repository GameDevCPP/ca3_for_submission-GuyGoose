#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  float _groundspeed;
  // Array of numbers to represent to represent lights
  std::vector<int> _lights;

  bool isGrounded() const;

public:
  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

    const std::vector<int> &getLights() const;

    void setLights(const std::vector<int> &lights);

    void addLight(int light);

    void removeLight(int light);

    PlayerPhysicsComponent() = delete;
};
