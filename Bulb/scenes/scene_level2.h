#pragma once

#include "engine.h"

class Level2Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;

    // Lights Vector
    std::vector<std::shared_ptr<Entity>> lights;

};