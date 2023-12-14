#pragma once

#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "ecm.h"

// Holds an array of points the taken in entity will follow, in order and reverse if needed

class PathComponent : public Component {
protected:
    bool _reverse = false;
    std::vector<sf::Vector2f> _path;
    size_t _current = 0;
    float _speed;
    std::shared_ptr<Entity> _follower;

public:
    PathComponent() = delete;

    explicit PathComponent(Entity* p, const std::vector<sf::Vector2f>& path, float speed, std::shared_ptr<Entity> follower);

    void update(double dt) override;

    void render() override;

    ~PathComponent() override = default;
};
