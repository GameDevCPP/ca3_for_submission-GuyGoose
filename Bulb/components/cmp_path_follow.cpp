
#include "cmp_path_follow.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"

PathComponent::PathComponent(Entity* p, const std::vector<sf::Vector2f>& path, float speed, std::shared_ptr<Entity> follower)
    : Component(p), _path(path), _speed(speed) {
    _current = 0;
    _follower = follower;

    // Set the position of the follower to the first point
    _follower->setPosition(_path[_current] + sf::Vector2f(-1.0f, 0.0f));
}

void PathComponent::update(double dt) {
    // Get the position of the follower
    sf::Vector2f pos = _follower->getPosition();
    // Get the position of the current point
    sf::Vector2f target = _path[_current];
    // Get the direction to the target
    sf::Vector2f dir = target - pos;
    // Get the length of the direction
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    // Normalise the direction
    dir = dir / static_cast<float>(len);
    // Move the follower
    pos += dir * static_cast<float>(_speed) * static_cast<float>(dt);
    // Set the position of the follower
    _follower->setPosition(pos);
    // Check if we have reached the target
    if (len < 5.0f) {
        // If we are in reverse mode
        if (_reverse) {
            // Go to the previous point
            _current--;
            // If we are at the start
            if (_current == 0) {
                // Go to forward mode
                _reverse = false;
            }
        }
        else {
            // Go to the next point
            _current++;
            // If we are at the end
            if (_current == _path.size()) {
                // Go to reverse mode
                _reverse = true;
                // Go to the previous point
                _current--;
            }
        }
    }
}

void PathComponent::render() {}